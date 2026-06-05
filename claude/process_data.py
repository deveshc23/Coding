import pandas as pd
import numpy as np
import json

# 1. Load the data
df = pd.read_csv('etf_prices.csv')

# Ensure date is in the correct string format (dates are in YYYY-MM-DD / ISO 8601 format)
df['date'] = pd.to_datetime(df['date'], format='%Y-%m-%d').dt.strftime('%Y-%m-%d')
df = df.sort_values('date').reset_index(drop=True)

dates = df['date'].tolist()
assets = [col for col in df.columns if col != 'date']

# 2. Calculate Returns
prices = df[assets]
daily_rets_df = prices.pct_change().fillna(0)

# 3. Simulate Strategies 
# (You will replace the BL logic with your actual quantitative model)
n_days = len(dates)
n_assets = len(assets)

# Equal Weight Strategy (Real calculation)
eq_weights = np.ones(n_assets) / n_assets
eq_daily_rets = daily_rets_df.dot(eq_weights)
eq_cum_rets = (1 + eq_daily_rets).cumprod()

# BL Multi-Factor (Placeholder mock data to test the UI)
# Simulating a strategy that slightly outperforms Equal Weight
bl_daily_rets = eq_daily_rets + np.random.normal(0.0002, 0.002, n_days)
bl_cum_rets = (1 + bl_daily_rets).cumprod()

# Mocking factor z-scores and dynamic weights for the UI
mock_weights = {asset: (np.random.dirichlet(np.ones(n_assets), n_days)[:, i]).tolist() for i, asset in enumerate(assets)}
mock_z_scores = {asset: np.random.normal(0, 1.5, n_days).tolist() for asset in assets}

# 4. Construct the JSON payload
viz_data = {
    "assets": assets,
    "dates": dates,
    "cum_rets": {
        "Equal Weight": eq_cum_rets.tolist(),
        "BL Multi-Factor": bl_cum_rets.tolist()
    },
    "daily_rets": {
        "Equal Weight": eq_daily_rets.tolist(),
        "BL Multi-Factor": bl_daily_rets.tolist()
    },
    "weights": {
        "values": mock_weights
    },
    "signals": {
        "dates": dates,
        "Q": np.random.uniform(0.05, 0.15, n_days).tolist(),     # View Q (ann.)
        "Omega": np.random.uniform(0.01, 0.05, n_days).tolist(), # Uncertainty
        "long_leg": ["SPY,EWJ" for _ in range(n_days)],          # Sample long targets
        "short_leg": ["EWG,EWC" for _ in range(n_days)],         # Sample short targets
        "z_scores": mock_z_scores
    }
}

# 5. Export to JSON
with open('viz_data.json', 'w') as f:
    json.dump(viz_data, f)

print(f"Successfully processed {n_days} days of data for {n_assets} assets.")
print("Saved to viz_data.json")