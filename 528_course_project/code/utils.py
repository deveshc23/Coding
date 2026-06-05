import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def setup_directories():
    """Creates necessary folders for data and figures."""
    os.makedirs(os.path.join(BASE_DIR, "data"), exist_ok=True)
    os.makedirs(os.path.join(BASE_DIR, "figures"), exist_ok=True)


# Plotting styles consistent with academic papers
def set_plot_style():
    """Sets matplotlib style for publication-quality figures."""
    sns.set_theme(style="whitegrid")
    plt.rcParams["figure.figsize"] = (10, 6)
    plt.rcParams["font.size"] = 12
    plt.rcParams["axes.labelsize"] = 14
    plt.rcParams["axes.titlesize"] = 16


# Annualization factors
TRADING_DAYS_PER_YEAR = 252


def annualize_return(mean_daily_return):
    """Converts daily mean return to annualized return."""
    return mean_daily_return * TRADING_DAYS_PER_YEAR


def annualize_vol(std_daily_return):
    """Converts daily std dev to annualized volatility."""
    return std_daily_return * np.sqrt(TRADING_DAYS_PER_YEAR)


def safe_inverse(matrix, ridge=1e-6):
    """
    Computes matrix inverse with a small ridge term to ensure numerical stability.
    Prevents singular matrix errors during optimization.
    """
    n = matrix.shape[0]
    return np.linalg.inv(matrix + ridge * np.eye(n))


def save_plot(fig, filename):
    """Saves a figure to the figures/ directory."""
    fig.savefig(os.path.join(BASE_DIR, "figures", filename), dpi=300, bbox_inches="tight")
    plt.close(fig)
