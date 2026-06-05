import pandas as pd
import numpy as np
import os
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from utils import safe_inverse

MARKET_CAP_WEIGHTS = {
    "US": 0.60,
    "Japan": 0.08,
    "UK": 0.06,
    "Germany": 0.05,
    "France": 0.05,
    "Canada": 0.04,
    "Switzerland": 0.04,
    "Australia": 0.03,
    "Netherlands": 0.03,
    "Sweden": 0.02,
}

ETF_TO_COUNTRY = {
    "SPY": "US",
    "EWJ": "Japan",
    "EWU": "UK",
    "EWG": "Germany",
    "EWQ": "France",
    "EWC": "Canada",
    "EWL": "Switzerland",
    "EWA": "Australia",
    "EWN": "Netherlands",
    "EWD": "Sweden",
}


def compute_equilibrium_returns(returns, window=252, risk_free_rate=0.0):
    assets = returns.columns

    try:
        w_eq = np.array([
            MARKET_CAP_WEIGHTS[ETF_TO_COUNTRY[col]]
            for col in assets
        ])
    except KeyError as e:
        raise ValueError(f"Missing mapping for ETF: {e}")

    w_eq = w_eq / w_eq.sum()

    dates = returns.index[window:]
    pi_history = []

    for i in range(window, len(returns)):
        window_data = returns.iloc[i - window : i]
        sigma = window_data.cov().values * 252

        port_returns = window_data @ w_eq
        rm = port_returns.mean() * 252
        var_m = port_returns.var() * 252

        if var_m <= 1e-8:
            var_m = 1e-8

        delta = (rm - risk_free_rate) / var_m
        pi = delta * sigma @ w_eq

        pi_history.append(pi)

    pi_df = pd.DataFrame(pi_history, index=dates, columns=assets)

    return pi_df, w_eq


def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    DATA_PATH = os.path.join(BASE_DIR, "data", "etf_prices.csv")
    OUTPUT_DIR = os.path.join(BASE_DIR, "data")

    prices = pd.read_csv(DATA_PATH, index_col=0, parse_dates=True)
    returns = np.log(prices / prices.shift(1)).dropna()

    pi_df, w_eq = compute_equilibrium_returns(returns)

    pi_df.to_csv(os.path.join(OUTPUT_DIR, "equilibrium_returns.csv"))

    pd.DataFrame(
        w_eq,
        index=returns.columns,
        columns=["Market Weight"]
    ).to_csv(os.path.join(OUTPUT_DIR, "market_weights.csv"))


if __name__ == "__main__":
    main()