import sys
import yfinance as yf

def get_last_stock_price(stock_symbol):
    try:
        stock = yf.Ticker(stock_symbol)
        hist = stock.history(period="1d")
        last_price = hist['Close'].iloc[-1]
        return last_price
    except Exception as e:
        print(f"Error fetching stock data: {e}")
        return None