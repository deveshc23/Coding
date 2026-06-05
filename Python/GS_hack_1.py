import pandas as pd
import numpy as np
from sklearn.linear_model import Lasso

def hedge_with_lasso(metadata, returns, portfolio_id, pnl_values, alpha=0.1):
    returns = returns.copy()
    returns[portfolio_id] = pnl_values
    
    stock_cols = [col for col in returns.columns if col not in ['Date', portfolio_id]]
    X = returns[stock_cols].values
    y = returns[portfolio_id].values
    
    lasso = Lasso(alpha=alpha, positive=False, max_iter=10000)
    lasso.fit(X, y)
    
    weights = lasso.coef_
    stocks = stock_cols
    
    hedge_df = pd.DataFrame({
        'Stock_Id': stocks,
        'Weight': weights
    })
    
    hedge_df = hedge_df[hedge_df['Weight'] != 0].copy()
    if hedge_df.empty:
        return []
    
    hedge_df['Quantity'] = (-hedge_df['Weight']).round().astype(int)
    hedge_df = hedge_df[hedge_df['Quantity'] != 0]
    
    return list(zip(hedge_df['Stock_Id'], hedge_df['Quantity']))


def main():
    returns = pd.read_csv("stocks_returns.csv")/100
    metadata = pd.read_csv("stocks_metadata.csv")
    input_line = input()
    parts = input_line.strip().split()
    
    portfolio_id = parts[0]
    pnl_values = list(map(float, parts[1:]))
    
    hedge_positions = hedge_with_lasso(metadata, returns, portfolio_id, pnl_values, alpha=0.1)
    for stock_id, qty in hedge_positions:
        print(f"{stock_id} {qty}")

        
if __name__ == '__main__':
    main()
