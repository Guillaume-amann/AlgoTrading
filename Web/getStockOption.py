import yfinance as yf
import csv
import os
from datetime import datetime

def fetch_call(ticker, csv_file="./Database/Call.csv"):
    stock = yf.Ticker(ticker)
    expiration_dates = stock.options
    stock_price = stock.history(period="1d")["Close"].iloc[0]  # Get the current stock price

    with open(csv_file, mode="w", newline="") as file:
        writer = csv.writer(file)
        
        writer.writerow(["StockPrice", "Strike", "LastPrice", "Maturity"])
        current_date = datetime.now()

        for expiration in expiration_dates:
            option_chain = stock.option_chain(expiration)
            calls = option_chain.calls

            expiration_date = datetime.strptime(expiration, "%Y-%m-%d")
            maturity_years = (expiration_date - current_date).days / 365.0

            for _, row in calls.iterrows():
                strike = row["strike"]
                last_price = row["lastPrice"]

                writer.writerow([stock_price, strike, last_price, maturity_years])

def fetch_put(ticker, csv_file="./Database/Put.csv"):

    stock = yf.Ticker(ticker)
    expiration_dates = stock.options
    stock_price = stock.history(period="1d")["Close"].iloc[0]  # Get the current stock price

    with open(csv_file, mode="w", newline="") as file:
        writer = csv.writer(file)
        
        writer.writerow(["StockPrice", "Strike", "LastPrice", "Maturity"])
        current_date = datetime.now()

        for expiration in expiration_dates:
            option_chain = stock.option_chain(expiration)
            puts = option_chain.puts

            expiration_date = datetime.strptime(expiration, "%Y-%m-%d")
            maturity_years = (expiration_date - current_date).days / 365.0

            for _, row in puts.iterrows():
                strike = row["strike"]
                last_price = row["lastPrice"]

                writer.writerow([stock_price, strike, last_price, maturity_years])