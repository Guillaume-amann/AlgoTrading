import yfinance as yf
import pandas as pd
from datetime import datetime

def fetch_options(ticker):
    """
    Fetches call and put options for a given stock ticker and stores them in CSV files.
    Includes only the specified columns and calculates maturity (time to expiration) in days.
    
    Parameters:
    ticker (str): The stock ticker symbol to fetch options for.
    """
    # Fetch the stock data
    stock = yf.Ticker(ticker)

    # Get available expiration dates
    expirations = stock.options

    call_options = []
    put_options = []

    # Retrieve options for each expiration date
    for expiration in expirations:
        options = stock.option_chain(expiration)

        # Calculate maturity in days
        maturity = (pd.to_datetime(expiration) - pd.to_datetime(datetime.now())).days

        # Select only the specified columns for call and put options
        calls_filtered = options.calls[['contractSymbol', 'lastTradeDate', 'strike', 'lastPrice']].copy()
        puts_filtered = options.puts[['contractSymbol', 'lastTradeDate', 'strike', 'lastPrice']].copy()

        # Add maturity to the filtered DataFrames
        calls_filtered['maturity'] = maturity
        puts_filtered['maturity'] = maturity

        # Append filtered call and put options to their respective lists
        call_options.append(calls_filtered)
        put_options.append(puts_filtered)

    # Concatenate all calls and puts into a single DataFrame
    all_calls = pd.concat(call_options, ignore_index=True)
    all_puts = pd.concat(put_options, ignore_index=True)

    # Store call and put options in CSV files
    all_calls.to_csv('Web/call.csv', index=False)
    all_puts.to_csv('Web/put.csv', index=False)

    print(f'Options for {ticker} have been saved to call.csv and put.csv.')

fetch_options('AAPL')