
from ig_trading_historical_data import IG_API
import user_info
from pprint import pprint 

demo = 1  
username = user_info.username
pw = user_info.pw
api_key = user_info.api_key

assets={
    'Spot Gold':{
        'instrument_name': 'Spot Gold', 
        'expiry': 'DFB'
    },
    'US 500': {  
        'instrument_name': 'US 500',  
        'expiry': 'DFB'
    },
}

resolution = 'MINUTE_5'
range_type = 'dates'
start_date = '2020-01-01 10:00:00'
end_date = '2025-01-01 10:30:00'
weekdays = (0, 2)
ig_api = IG_API(demo, username, pw, api_key)
assets = ig_api.get_epics(assets)
pprint(assets)

assets, allowance = ig_api.get_prices_all_assets(
    assets, 
    resolution, 
    range_type, 
    start_date,
    end_date,
    weekdays,
)

print(assets['Spot Gold']['prices'])
