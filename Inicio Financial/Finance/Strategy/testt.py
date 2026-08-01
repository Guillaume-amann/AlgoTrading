import yfinance as yf

# Ticker symbol of the stock (e.g., Apple)
ticker_symbol = "AAPL"

# Create a Ticker object
ticker = yf.Ticker(ticker_symbol)

# Get the options data for a specific expiry date
options_data = ticker.option_chain('2024-03-22')  # Change the expiry date as needed

# Print the call options data
print("Call Options:")
print(options_data.calls)

# Print the put options data
print("\nPut Options:")
print(options_data.puts)