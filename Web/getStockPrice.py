import yfinance as yf

def YTD(ticker):
    try:
        stock = yf.Ticker(ticker)
        hist = stock.history(period="2y")

        if len(hist) >= 252:
            prices = hist['Close'].iloc[-252:].tolist()
            dates = [str(date.date()) for date in hist.index[-252:]]
        else:
            print(f"Warning: Only {len(hist)} trading days available.")
            prices = hist['Close'].tolist()
            dates = [str(date.date()) for date in hist.index]
        
        return prices, dates  # Return as a tuple
        
    except Exception as e:
        print(f"Error fetching YTD stock data: {e}")
        return None, None