import os
import pandas as pd

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(BASE_DIR, "data")

FILES = {
    "SPY": "spy_us_d.csv",
    "EWU": "ewu_us_d.csv",
    "EWJ": "ewj_us_d.csv",
    "EWG": "ewg_us_d.csv",
    "EWQ": "ewq_us_d.csv",
    "EWC": "ewc_us_d.csv",
    "EWL": "ewl_us_d.csv",
    "EWA": "ewa_us_d.csv",
    "EWN": "ewn_us_d.csv",
    "EWD": "ewd_us_d.csv",
}


def load_and_clean(file_path):
    df = pd.read_csv(file_path)
    df.columns = [c.strip().lower() for c in df.columns]
    df["date"] = pd.to_datetime(df["date"], format="mixed", errors="coerce")
    df = df.dropna(subset=["date"])
    df = df.sort_values("date")
    df = df[["date", "close"]]
    df = df.drop_duplicates(subset="date")
    return df.set_index("date")


def main():
    all_data = []
    for ticker, file in FILES.items():
        path = os.path.join(DATA_DIR, file)
        df = load_and_clean(path)
        df.rename(columns={"close": ticker}, inplace=True)
        all_data.append(df)

    prices = pd.concat(all_data, axis=1)
    prices = prices.sort_index()
    # prices = prices[prices.index <= "2025-01-01"]
    prices = prices.ffill().bfill()
    prices = prices.dropna()

    output_path = os.path.join(DATA_DIR, "etf_prices.csv")
    prices.to_csv(output_path)


if __name__ == "__main__":
    main()
