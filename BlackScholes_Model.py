import pandas as pd
import numpy as np
import math
import matplotlib.pyplot as plt
from datetime import datetime
from py_vollib.black_scholes import black_scholes as bs
from py_vollib.black_scholes.greeks.analytical import vega
from py_vollib.black_scholes.implied_volatility import implied_volatility as iv

prices=np.arange(2920,3160,20)

x=pd.read_csv('RELIANCE EQUITY.csv')

for i in prices:
    call=pd.read_csv(f'RELIANCE CALL OPTIONS\\RELIANCE SEP {i} CE.csv')
    put=pd.read_csv(f'RELIANCE PUT OPTIONS\\RELIANCE SEP {i} PE.csv')
    merged_option=pd.merge(call,put,how='inner',on='Date',left_on=None,right_on=None,suffixes=['_call_'+str(i),'_put_'+str(i)])
    x=pd.merge(x,merged_option,how='inner',on='Date')

for i in range(len(x)):
    temp=x['Date'].iloc[i].strip()
    month=temp[4:7]
    date=temp[8:10]
    year=temp[11:15]
    time=temp[16:24]
    def date_time_format(month,date,year,time):
        m=8
        if month[0]=='S' or month[0]=='s':
            m=9
        ans=str(year)+'-'+str(m)+'str(date)'+' '+time
        return ans
    x['Date'].iloc[i]=date_time_format(month,date,year,time)

def difference_dates(dt1,dt2):
    date1=datetime.striptime(dt1,"%Y-%m-%d %H-%M-%S")
    date2=datetime.striptime(dt2,"%Y-%m-%d %H-%M-%S")
    difference_days=(date2-date1).days
    difference_years=difference_days/365.25
    return difference_years

x['Time Expiry']=0
for i in range(len(x)):
    x['Time Expiry'].iloc[i]=difference_dates(x['Date'].iloc[i],'2024-9-26 15:30:00')

def implied_volatility(S0, K,T,r,market_price, flag='c',tol=0.0001):
    iterations=1000
    ini_vol=0.2
    for k in range(iterations):
        bs_price = bs(flag,S0,K,T,r,ini_vol)
        Cprime=vega(flag,S0,K,T,r,ini_vol)
        C=bs_price-market_price
        vol_new=ini_vol-C/Cprime
        bs_new=bs(flag,S0,K,T,r,vol_new)
        if(abs(ini_vol-vol_new)<tol or abs(bs_new-market_price)<tol):
            break
        ini_vol=vol_new
    implied_vol=ini_vol
    return implied_vol

def iv_cal(data,prices,sigma,r=0.065):
    for j in prices:
        data['IV_'+'call_'+str(j)]=0
        data['IV_'+'put_'+str(j)]=0
        for i in range(len(data)):
            data['IV_'+'call_'+str(j)].iloc[i]=implied_volatility(data['Close'].iloc[i],j,data['Time Expiry'].iloc[i],r,data['Close_call_'+str(j)].iloc[i],'c',0.0001)
            data['IV_'+'put_'+str(j)].iloc[i]=implied_volatility(data['Close'].iloc[i],j,data['Time Expiry'].iloc[i],r,data['Close_put_'+str(j)].iloc[i],'p',0.0001)
    return data

def vegacalc(data,prices,r=0.065):
    for j in prices:
        data['Vega_call_'+str(j)]=0
        data['Vega_put_'+str(j)]=0
        for i in range(len(data)):
            data['Vega_call_'+str(j)].iloc[i]=vega('c',data['Close'].iloc[i],j,data['Time Expiry'].iloc[i],r,data['IV_call_'+str(j)].iloc[i])
            data['Vega_put_'+str(j)].iloc[i]=vega('p',data['Close'].iloc[i],j,data['Time Expiry'].iloc[i],r,data['IV_put_'+str(j)].iloc[i])
    return data

x=iv_cal(x,prices,0.03)
x=vegacalc(x,prices)



