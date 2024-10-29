import sys
import yfinance as yf

def YTD(ticker):
    try:
        stock = yf.Ticker(ticker)
        hist = stock.history(period="2y")
        # Check if there are at least 252 entries
        if len(hist) >= 252:
            return list(hist['Close'].iloc[-252:])  # Return the last 252 prices
        else:
            print(f"Warning: Only {len(hist)} trading days available.")
            return list(hist['Close'])  # Return all available prices if less than 252
    except Exception as e:
        print(f"Error fetching YTD stock data: {e}")
        return None