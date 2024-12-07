import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from hmmlearn.hmm import GaussianHMM

def calculate_atr(close,high,open,low):
    atr_period=14
    range=high-low
    high_close_prev=abs(high-close.shift(1))
    low_close_prev=abs(low-close.shift(1))
    tr = pd.concat([range, high_close_prev, low_close_prev], axis=1).max(axis=1)
    atr=tr.rolling(atr_period).mean()
    return atr

def HMM(df):
    df['EMA']=df['Close'].ewm(span=14,adjust=False).mean()
    df['Log Returns']=df['Close']/df['Close'].shift(1)
    df['ATR']=calculate_atr(df['Close'],df['High'],df['Open'],df['Low'])
    x=df[['ATR']].values
    hmm_model=GaussianHMM(n_components=3,covariance_type='full',n_iter=100)
    hmm_model.fit()

    df['Hidden State']=hmm_model.predict(x)
    state_regime_map={0:'Low Volatility',1:'High Volatility',2:'High Volatility'}
    df['Volatility Regime']=df['Hidden States'].map(state_regime_map)
    multiplier_map={
        'Low Volatility':3.0,
        'Medium Volatility':2.0,
        'High Volatility':1.5
    }
    df['ATR Multiplier']=df['Volatility Regime'].map(multiplier_map)

    df['Upper Band']=df['EMA']+df['ATR']*df['ATR Multiplier']
    df['Lower Band']=df['EMA']-df['ATR']*df['ATR Multiplier']
    return df



