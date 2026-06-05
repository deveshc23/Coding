# 1. Clear the environment and close any stuck plot windows
rm(list=ls())
graphics.off() 

# 2. Load Libraries
library(quantmod)
library(moments)

# 3. Get Data (BSE Sensex)
start_date <- as.Date("2000-01-01") 
end_date <- as.Date("2025-12-31") 
getSymbols("^BSESN", src = "yahoo", from = start_date, to = end_date)
prices <- Ad(BSESN)
returns <- na.omit(diff(log(prices)) * 100)

# --- Question 1: Summary Statistics ---
m_val <- mean(returns) 
s_val <- sd(returns) 
cat("\n--- Q1: Numerical Values ---")
cat("\nMean Daily Return:", round(m_val, 5))
cat("\nDaily Volatility (SD):", round(s_val, 5))

# --- Question 2: Serial Correlation ---
dev.new() # FORCES a new window to open
acf(returns, main="Q2: ACF of Daily Returns") 
cat("\n\n--- Q2: Numerical Values ---")
print(Box.test(returns, lag = 1, type = "Ljung-Box"))

# --- Question 3: Volatility Clustering ---
dev.new() 
par(mfrow=c(2,1)) # Splits window: Top for Returns, Bottom for Squared ACF
plot(returns, main="Q3: Daily Returns Time Series") 
acf(returns^2, main="Q3: ACF of Squared Returns") 

# --- Question 4: Non-normality ---
cat("\n\n--- Q4: Numerical Values ---")
cat("\nSkewness:", round(skewness(returns), 5))
cat("\nKurtosis:", round(kurtosis(returns), 5))

dev.new()
hist(returns, breaks=100, probability=TRUE, main="Q4: Return Distribution", col="skyblue")
curve(dnorm(x, mean=m_val, sd=s_val), add=TRUE, col="red", lwd=2) 

# --- Question 5: Leverage Effect ---
lag_ret <- lag(returns, 1)
sq_ret <- returns^2
lev_corr <- cor(lag_ret, sq_ret, use="complete.obs")
cat("\n\n--- Q5: Numerical Values ---")
cat("\nLeverage Correlation (Lagged Return vs Volatility):", round(lev_corr, 5))