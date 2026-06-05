import os
import sys
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from utils import setup_directories, set_plot_style, save_plot


def main():
    setup_directories()
    set_plot_style()

    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    DATA_PATH = os.path.join(BASE_DIR, "data", "etf_prices.csv")

    prices = pd.read_csv(DATA_PATH, index_col=0, parse_dates=True)

    returns = np.log(prices / prices.shift(1)).dropna()

    stats = pd.DataFrame({
        "Annualized Mean": returns.mean() * 252,
        "Annualized Vol": returns.std() * np.sqrt(252),
        "Sharpe Ratio": (returns.mean() * 252) / (returns.std() * np.sqrt(252)),
        "Skewness": returns.skew(),
        "Kurtosis": returns.kurtosis(),
    })

    stats_path = os.path.join(BASE_DIR, "data", "descriptive_stats.csv")
    stats.to_csv(stats_path)

    fig, ax = plt.subplots(figsize=(12, 6))
    cum_returns = (1 + returns).cumprod()
    cum_returns.plot(ax=ax, title="Cumulative Returns of 10 Country Indices")
    ax.set_ylabel("Growth of $1")
    save_plot(fig, "01_cumulative_returns.png")

    corr_matrix = returns.corr()
    corr_path = os.path.join(BASE_DIR, "data", "correlation_matrix.csv")
    corr_matrix.to_csv(corr_path)

    fig, ax = plt.subplots(figsize=(10, 8))
    sns.heatmap(corr_matrix, annot=True, fmt=".2f", cmap="coolwarm", ax=ax)
    plt.title("Correlation Matrix of Daily Returns")
    save_plot(fig, "02_correlation_matrix.png")


if __name__ == "__main__":
    main()
