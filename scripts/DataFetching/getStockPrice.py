import yfinance as yf
import pandas as pd
import datetime as dt
from pathlib import Path


PRICE_CACHE = Path("scripts/Database/cache/prices.csv")

df = pd.read_csv("scripts/Database/Universe.csv")
tickers = df.columns.tolist()[:-1] # Assuming "T1,...,Tn,Date"
stock_data = pd.DataFrame()

for ticker in tickers:
    stock = yf.Ticker(ticker)
    data = stock.history(period="2y")  # Fetch the last 300 days of data
    stock_data[ticker] = data['Close'][-252:]  # Keep only the last 252 values

stock_data['Date'] = stock_data.index[-252:].strftime('%Y-%m-%d')  # Convert index to string dates
stock_data.to_csv("scripts/Database/Universe.csv", index=False)

def load_prices(tickers, start, end, force_reload=False):
    """
    Load prices from cache or Yahoo Finance.
    force_reload: if True, always fetch from Yahoo even if cache exists
    """
    tickers = sorted(set(tickers))
    
    if PRICE_CACHE.exists() and not force_reload:
        prices = pd.read_csv(PRICE_CACHE, index_col=0, parse_dates=True)
        max_date = prices.index.max()
        # if cache is recent enough, return intersecting tickers
        if (dt.datetime.now().date() - max_date.date()).days < 3:
            missing = [t for t in tickers if t not in prices.columns]
            if missing:
                # fetch missing tickers only
                new_raw = yf.download(missing, start=start, end=end, auto_adjust=True)
                new_prices = new_raw['Close'] if 'Close' in new_raw else new_raw
                new_prices = new_prices.sort_index().ffill().bfill()
                prices = pd.concat([prices, new_prices], axis=1)
                prices = prices[tickers]  # keep only requested columns
                prices.to_csv(PRICE_CACHE)
            else:
                prices = prices[tickers]
            return prices

    # fetch everything if force_reload or cache missing/outdated
    raw = yf.download(tickers, start=start, end=end, auto_adjust=True)
    prices = raw['Close'] if 'Close' in raw else raw
    prices = prices.sort_index().ffill().bfill()
    
    # update cache
    PRICE_CACHE.parent.mkdir(exist_ok=True, parents=True)
    if PRICE_CACHE.exists():
        old_cache = pd.read_csv(PRICE_CACHE, index_col=0, parse_dates=True)
        prices = pd.concat([old_cache, prices], axis=1)
        prices = prices.loc[:, ~prices.columns.duplicated()]
    prices.to_csv(PRICE_CACHE)
    
    return prices[tickers]