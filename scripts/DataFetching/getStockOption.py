import yfinance as yf
from datetime import datetime

def fetch_options(ticker, call_csv_file="./Database/Call.csv", put_csv_file="./Database/Put.csv"):
    stock = yf.Ticker(ticker)
    expiration_dates = stock.options
    stock_price = stock.history(period="1d")["Close"].iloc[0]  # Get the current stock price
    current_date = datetime.now()

    with open(call_csv_file, "w") as file:
        file.write("StockPrice,Strike,LastPrice,Maturity\n")
        for expiration in expiration_dates:
            option_chain = stock.option_chain(expiration)
            calls = option_chain.calls
            expiration_date = datetime.strptime(expiration, "%Y-%m-%d")
            maturity_years = (expiration_date - current_date).days / 365.0
            for _, row in calls.iterrows():
                file.write(f"{stock_price},{row['strike']},{row['lastPrice']},{maturity_years}\n")

    with open(put_csv_file, "w") as file:
        file.write("StockPrice,Strike,LastPrice,Maturity\n")
        for expiration in expiration_dates:
            option_chain = stock.option_chain(expiration)
            puts = option_chain.puts
            expiration_date = datetime.strptime(expiration, "%Y-%m-%d")
            maturity_years = (expiration_date - current_date).days / 365.0
            for _, row in puts.iterrows():
                file.write(f"{stock_price},{row['strike']},{row['lastPrice']},{maturity_years}\n")