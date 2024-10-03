import os
os.environ['TF_ENABLE_ONEDNN_OPTS'] = '0'
import pandas as pd
import numpy as np
import yfinance as yf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import tensorflow 
from keras.models import Sequential
from tensorflow.keras.layers import Dense,Dropout
from tensorflow.keras import regularizers
import matplotlib.pyplot as plt

ticker='AAPL'
start_date='2015-01-01'
end_date='2023-01-01'
data=yf.download(ticker,start=start_date,end=end_date)
print(data.tail())

data['Returns']=np.log(data['Adj Close']/data['Adj Close'].shift(1))
data.dropna(inplace=True)
def create_lagged_returns(returns,g):
    return pd.concat([returns.shift(i) for i in range(1,g+1)],axis=1).dropna()
features=create_lagged_returns(data['Close'],15)
target=data['Close'][15:]

def scale_data(train,test):
    if scaler is None:
        scaler=StandardScaler()
        train_scaled=scaler.fit_transform(train)
    else:
        train_scaled=scaler.transform(test)
    test_scaled = scaler.transform(test)
    return train_scaled,test_scaled,scaler
scaler=StandardScaler()
X_train=scaler.fit_transform(X_train)
X_test=scaler.fit_transform(X_test)

current_prices = target.iloc[-len(X_test):]

#CREATING THE MODEL
def build_model(input_dim):
    model=Sequential()
    input_dim=X_train.shape[1]
    model.add(Dense(32,input_dim=input_dim,activation='relu'))
    model.add(Dense(64,activation='relu'))
    model.add(Dense(32,activation='relu'))
    model.add(Dense(8,activation='relu'))
    model.add(Dense(1,activation='linear'))
    model.compile(optimizer='adam',loss='mse')
    return model

train_window=20
predict_window=5

history=model.fit(X_train,y_train,epochs=50,batch_size=32,validation_data=(X_test,y_test))
loss=model.evaluate(X_test,y_test)
print(f'Test Loss(MSE):{loss}')

predictions=model.predict(X_test)

signals = np.where(predictions.flatten() > current_prices.values, 1, -1)

#BACKTESTING
initial_capital=10000
capital=initial_capital
x=0
trade_log=[]

for i in range(len(signals)-1):
    current_price=current_prices.iloc[i]
    if signals[i]==1 and x ==0:
        x=1
        buy_price=current_price
        position=capital//buy_price
        capital-=position*buy_price
        trade_log.append(f"BUY at {buy_price} on day {i}")
    elif signals[i]==-1 and x==1:
        x=0
        sell_price=current_price
        capital+=position*sell_price
        profit_or_loss=(sell_price-buy_price)*position
        trade_log.append(f"SELL at {sell_price} on day {i} with a profit/loss of {profit_or_loss}")
if x==1:
    sell_price=current_prices.iloc[-1]
    capital+=sell_price*position
    profit_or_loss=(sell_price-buy_price)*position
    trade_log.append(f"SELL at {sell_price} on last day with a profit/loss of {profit_or_loss}")

# plt.plot(y_test.values,label='True Returns')
# plt.plot(predictions,label='Predicted Values')
# plt.legend()
# plt.show()

print(f"Initial Capital: {initial_capital}")
print(f"Final Capital: {capital}")
print(trade_log)