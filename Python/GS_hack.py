import numpy as np
import pandas as pd
from scipy.interpolate import RegularGridInterpolator
import io

# --- 1. PARAMETERS ---

spot_prices = np.array([100, 100, 100])  # DTC, DFC, DEC
risk_free_rate = 0.05
corr_matrix = np.array([
    [1.0, 0.8, 0.75],
    [0.8, 1.0, 0.85],
    [0.75, 0.85, 1.0]
])
strikes = [50, 75, 100, 125, 150]
maturities = [1, 2, 5]

local_vol_DTC = np.array([
    [0.2205, 0.2240, 0.2248],
    [0.1994, 0.1998, 0.2001],
    [0.1999, 0.2000, 0.2000],
    [0.1998, 0.2000, 0.2000],
    [0.2000, 0.2000, 0.1999]
])
local_vol_DFC = np.array([
    [0.2607, 0.2619, 0.2624],
    [0.2151, 0.2154, 0.2154],
    [0.1999, 0.2000, 0.2000],
    [0.2155, 0.2156, 0.2156],
    [0.2623, 0.2624, 0.2624]
])
local_vol_DEC = np.array([
    [0.2205, 0.2240, 0.2248],
    [0.2120, 0.2125, 0.2122],
    [0.1999, 0.2000, 0.2000],
    [0.1874, 0.1875, 0.1874],
    [0.1745, 0.1746, 0.1750]
])
vol_surfaces = [local_vol_DTC, local_vol_DFC, local_vol_DEC]

def get_interpolators(vol_surface):
    return RegularGridInterpolator((strikes, maturities), vol_surface)

interpolators = [get_interpolators(vol) for vol in vol_surfaces]

# --- 2. MONTE CARLO SIMULATION ---

def simulate_basket_price(knockout, maturity_yrs, strike, option_type, 
                          num_paths=10000, steps_per_year=52):

    dt = 1 / steps_per_year
    steps = int(maturity_yrs * steps_per_year)
    dim = len(spot_prices)

    chol = np.linalg.cholesky(corr_matrix)
    prices = np.full((num_paths, dim), spot_prices, dtype=np.float64)

    basket_prices = np.zeros((num_paths, steps + 1))
    basket_prices[:, 0] = np.mean(prices, axis=1)

    for t in range(1, steps + 1):
        Z = np.random.normal(size=(num_paths, dim))
        correlated_Z = Z @ chol.T

        for i in range(dim):
            S = prices[:, i]
            t_years = t * dt
            vol = interpolators[i]((np.clip(S, 50, 150), np.full(S.shape, maturity_yrs)))
            dS = risk_free_rate * S * dt + vol * S * np.sqrt(dt) * correlated_Z[:, i]
            prices[:, i] += dS

        basket_prices[:, t] = np.mean(prices, axis=1)

    knocked_out = np.any(basket_prices >= knockout, axis=1)

    final_prices = basket_prices[:, -1]
    if option_type.lower() == 'call':
        payoffs = np.maximum(final_prices - strike, 0)
    else:
        payoffs = np.maximum(strike - final_prices, 0)

    payoffs[knocked_out] = 0
    discounted = np.exp(-risk_free_rate * maturity_yrs) * payoffs
    return np.mean(discounted)

# --- 3. EMBEDDED INPUT CSV ---

input_csv = """
Id,Asset,KnockOut,Maturity,Strike,Type
1,Basket,150,2y,50,Call
2,Basket,175,2y,50,Call
3,Basket,200,2y,50,Call
4,Basket,150,5y,50,Call
5,Basket,175,5y,50,Call
6,Basket,200,5y,50,Call
7,Basket,150,2y,100,Call
8,Basket,175,2y,100,Call
9,Basket,200,2y,100,Call
10,Basket,150,5y,100,Call
11,Basket,175,5y,100,Call
12,Basket,200,5y,100,Call
13,Basket,150,2y,125,Call
14,Basket,175,2y,125,Call
15,Basket,200,2y,125,Call
16,Basket,150,5y,125,Call
17,Basket,175,5y,125,Call
18,Basket,200,5y,125,Call
19,Basket,150,2y,75,Put
20,Basket,175,2y,75,Put
21,Basket,200,2y,75,Put
22,Basket,150,5y,75,Put
23,Basket,175,5y,75,Put
24,Basket,200,5y,75,Put
25,Basket,150,2y,100,Put
26,Basket,175,2y,100,Put
27,Basket,200,2y,100,Put
28,Basket,150,5y,100,Put
29,Basket,175,5y,100,Put
30,Basket,200,5y,100,Put
31,Basket,150,2y,125,Put
32,Basket,175,2y,125,Put
33,Basket,200,2y,125,Put
34,Basket,150,5y,125,Put
35,Basket,175,5y,125,Put
36,Basket,200,5y,125,Put
"""

input_df = pd.read_csv(io.StringIO(input_csv.strip()))

# --- 4. PROCESSING ---

output = []

for _, row in input_df.iterrows():
    id_, ko, maturity_str, strike, opt_type = row['Id'], row['KnockOut'], row['Maturity'], row['Strike'], row['Type']
    maturity = int(maturity_str.strip('y'))
    price = simulate_basket_price(knockout=ko, maturity_yrs=maturity, strike=strike, option_type=opt_type)
    output.append((id_, round(price, 2)))

output_df = pd.DataFrame(output, columns=["Id", "Price"])
print(output_df.to_csv(index=False))
