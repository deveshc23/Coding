import os
import sys
import importlib

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(os.path.dirname(os.path.abspath(__file__)))


def run_pipeline():
    download_data = importlib.import_module('01_download_data')
    descriptive_stats = importlib.import_module('02_descriptive_stats')
    equilibrium = importlib.import_module('03_equilibrium_returns')
    momentum = importlib.import_module('04_momentum_views')
    backtest = importlib.import_module('06_backtest')
    analysis = importlib.import_module('07_analysis')

    download_data.main()
    descriptive_stats.main()
    equilibrium.main()
    momentum.main()
    backtest.main()
    analysis.main()


if __name__ == "__main__":
    run_pipeline()
