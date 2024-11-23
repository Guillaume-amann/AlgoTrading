import yfinance as yf
import pandas as pd

df = pd.read_csv("Database/Universe.csv")
tickers = df.columns.tolist()[:-1] # Assuming "T1,...,Tn,Date"
stock_data = pd.DataFrame()

for ticker in tickers:
    stock = yf.Ticker(ticker)
    data = stock.history(period="2y")  # Fetch the last 300 days of data
    stock_data[ticker] = data['Close'][-252:]  # Keep only the last 252 values

stock_data['Date'] = stock_data.index[-252:].strftime('%Y-%m-%d')  # Convert index to string dates
stock_data.to_csv("Database/Universe.csv", index=False)