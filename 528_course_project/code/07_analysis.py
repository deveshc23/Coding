import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import os
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from utils import setup_directories, set_plot_style, save_plot


def calculate_metrics(returns_df):
    metrics = {}
    for col in returns_df.columns:
        r = returns_df[col]
        ann_ret = r.mean() * 252
        ann_vol = r.std() * np.sqrt(252)
        sharpe = ann_ret / ann_vol if ann_vol > 0 else 0
        cum_ret = (1 + r).cumprod()
        max_dd = (cum_ret / cum_ret.cummax() - 1).min()
        abs_ret = (cum_ret.iloc[-1] - 1)

        metrics[col] = {
            "Ann. Return": ann_ret,
            "Ann. Vol": ann_vol,
            "Sharpe": sharpe,
            "Max Drawdown": max_dd,
            "Total Return": abs_ret,
        }
    return pd.DataFrame(metrics)


def main():
    setup_directories()
    set_plot_style()

    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    DATA_DIR = os.path.join(BASE_DIR, "data")

    ret_df = pd.read_csv(os.path.join(DATA_DIR, "backtest_returns.csv"), index_col=0, parse_dates=True)

    metrics = calculate_metrics(ret_df)
    print(metrics.to_string())
    print()

    cum_wealth = (1 + ret_df).cumprod()

    metrics.to_csv(os.path.join(DATA_DIR, "performance_metrics.csv"))
    cum_wealth.to_csv(os.path.join(DATA_DIR, "cumulative_wealth.csv"))


if __name__ == "__main__":
    main()
