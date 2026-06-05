import pandas as pd
import numpy as np
import os
import sys
from scipy import stats

sys.path.append(os.path.dirname(os.path.abspath(__file__)))


def _zscore_cross_section(series: pd.Series) -> pd.Series:
    mu = series.mean()
    sigma = series.std()
    if sigma == 0 or np.isnan(sigma):
        return pd.Series(np.zeros(len(series)), index=series.index)
    return (series - mu) / sigma


def _compute_r2(log_prices: np.ndarray) -> float:
    if len(log_prices) < 5:
        return 0.0
    x = np.arange(len(log_prices))
    slope, intercept, r_value, p_value, std_err = stats.linregress(x, log_prices)
    return float(np.sign(slope)) * r_value ** 2


def _compute_signals_at_t(window_returns: pd.DataFrame,
                           window_prices: pd.DataFrame) -> pd.DataFrame:
    signals = pd.DataFrame(index=window_returns.columns)
    signals["CSM"] = window_returns.sum()
    r2_vals = {}
    for asset in window_prices.columns:
        log_p = np.log(window_prices[asset].replace(0, np.nan).dropna().values)
        r2_vals[asset] = _compute_r2(log_p)
    signals["R2"] = pd.Series(r2_vals)
    return signals


def construct_momentum_views(
    returns: pd.DataFrame,
    prices: pd.DataFrame = None,
    lookback_days: int = 189,
    k: int = 2,
    alpha: float = 0.05,
    factor_weights: dict = None,
) -> tuple:
    assets = returns.columns
    n_assets = len(assets)
    k = max(1, min(k, n_assets // 2))

    if prices is None:
        prices = np.exp(returns.cumsum()) * 100

    default_weights = {"CSM": 0.50, "R2": 0.50}
    if factor_weights is not None:
        default_weights.update(factor_weights)
    fw = default_weights

    views_data = []
    omega_data = []
    p_list = []
    dates = []

    for i in range(lookback_days, len(returns)):
        window_ret = returns.iloc[i - lookback_days: i]
        window_px = prices.iloc[i - lookback_days: i]

        raw = _compute_signals_at_t(window_ret, window_px)
        z_factors = raw.apply(_zscore_cross_section)

        composite = (
            fw["CSM"] * z_factors["CSM"]
            + fw["R2"] * z_factors["R2"]
        )

        z_final = _zscore_cross_section(composite)

        ranked = z_final.sort_values(ascending=False)
        long_assets = ranked.index[:k]

        p_vector = np.zeros(n_assets)
        asset_idx = {asset: j for j, asset in enumerate(assets)}
        for asset in long_assets:
            p_vector[asset_idx[asset]] = +1.0 / k

        daily_long = window_ret[long_assets].mean(axis=1)
        
        # Scale Q from z-score units to return units using portfolio volatility
        # This ensures Q and π (equilibrium returns) are in comparable units
        portfolio_vol = daily_long.std() * np.sqrt(252)
        q_value = (alpha * z_final[long_assets].mean()) * portfolio_vol

        omega = float(daily_long.var() * 252)
        omega = max(omega, 1e-8)

        current_date = returns.index[i]
        dates.append(current_date)
        views_data.append(q_value)
        omega_data.append(omega)
        p_list.append(p_vector)

    views_df = pd.DataFrame({"Q": views_data, "Omega": omega_data}, index=dates)
    p_cols = [f"P_{col}" for col in assets]
    p_matrix = pd.DataFrame(p_list, index=dates, columns=p_cols)

    return views_df, p_matrix


def main():
    BASE_DIR  = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    DATA_PATH = os.path.join(BASE_DIR, "data", "etf_prices.csv")
    OUTPUT_DIR = os.path.join(BASE_DIR, "data")

    prices  = pd.read_csv(DATA_PATH, index_col=0, parse_dates=True)
    returns = np.log(prices / prices.shift(1)).dropna()

    views_df, p_matrix = construct_momentum_views(
        returns,
        prices=prices,
        lookback_days=189,
        k=4,
        alpha=0.05,
    )

    views_df.to_csv(os.path.join(OUTPUT_DIR, "momentum_views_summary.csv"))
    p_matrix.to_csv(os.path.join(OUTPUT_DIR, "momentum_pick_matrix.csv"))




if __name__ == "__main__":
    main()