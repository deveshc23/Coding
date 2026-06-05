import pandas as pd
import numpy as np
import os
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from utils import setup_directories
import importlib

equilibrium = importlib.import_module('03_equilibrium_returns')
momentum = importlib.import_module('04_momentum_views')
bl_model = importlib.import_module('05_black_litterman')


def run_backtest(returns, prices=None, start_date='2010-01-01'):
    setup_directories()

    returns = returns[returns.index >= start_date]
    if prices is not None:
        prices = prices[prices.index >= start_date]

    pi_hist, w_eq = equilibrium.compute_equilibrium_returns(returns, window=252)
    views_df, p_matrix = momentum.construct_momentum_views(
        returns, prices=prices, lookback_days=189, k=2, alpha=0.05
    )

    common_dates = pi_hist.index.intersection(views_df.index).intersection(returns.index)

    port_returns = {
        'Equal Weight': [],
        'Market Cap': [],
        'Classical MV': [],
        'BL Equilibrium': [],
        'BL Momentum': []
    }

    weights_history = {
        'Market Cap': [],
        'BL Momentum': []
    }



    tau = 0.25  # increased from 0.05 → views now meaningfully influence the posterior
    risk_aversion = 2.5
    assets = returns.columns
    n = len(assets)

    for i, date in enumerate(common_dates[:-1]):
        try:
            row_pi = pi_hist.loc[date].values
            row_views = views_df.loc[date]
            
            window = returns.loc[:date].tail(252)
            sigma = window.cov().values * 252

            w_ew = np.ones(n) / n
            w_mkt = np.array([w_eq[j] for j in range(n)])

            mu_sample = window.mean().values * 252
            sigma_sample = window.cov().values * 252
            w_mv = bl_model.optimal_weights(mu_sample, sigma_sample, risk_aversion)

            w_bl_eq = bl_model.optimal_weights(row_pi, sigma, risk_aversion)

            p_vec = p_matrix.loc[date].values.reshape(-1, n)
            q_val = np.array([[row_views['Q']]])
            omega_val = np.array([[row_views['Omega']]])

            mu_bl_mom, v_post = bl_model.black_litterman_posterior(
                row_pi, sigma, p_vec, q_val, omega_val, tau=tau
            )
            w_bl_mom = bl_model.optimal_weights(mu_bl_mom, sigma + v_post, risk_aversion)

            weights_history['Market Cap'].append(w_mkt)
            weights_history['BL Momentum'].append(w_bl_mom)

            current_idx = returns.index.get_loc(date)
            if current_idx + 1 < len(returns):
                next_ret = returns.iloc[current_idx + 1].values

                port_returns['Equal Weight'].append(next_ret @ w_ew)
                port_returns['Market Cap'].append(next_ret @ w_mkt)
                port_returns['Classical MV'].append(next_ret @ w_mv)
                port_returns['BL Equilibrium'].append(next_ret @ w_bl_eq)
                port_returns['BL Momentum'].append(next_ret @ w_bl_mom)

        except Exception as e:
            print(f"Error at {date}: {e}")
            continue

    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    ret_df = pd.DataFrame(port_returns, index=common_dates[:-1])
    weights_df_mkt = pd.DataFrame(weights_history['Market Cap'], index=common_dates[:-1], columns=assets)
    weights_df_bl = pd.DataFrame(weights_history['BL Momentum'], index=common_dates[:-1], columns=assets)

    ret_df.to_csv(os.path.join(BASE_DIR, "data", "backtest_returns.csv"))
    weights_df_mkt.to_csv(os.path.join(BASE_DIR, "data", "weights_market_cap.csv"))
    weights_df_bl.to_csv(os.path.join(BASE_DIR, "data", "weights_bl_momentum.csv"))

    return ret_df


def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    prices = pd.read_csv(os.path.join(BASE_DIR, "data", "etf_prices.csv"), index_col=0, parse_dates=True)
    returns = np.log(prices / prices.shift(1)).dropna()
    run_backtest(returns, prices=prices, start_date='2010-01-01')


if __name__ == "__main__":
    main()
