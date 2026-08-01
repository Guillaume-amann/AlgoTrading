import pandas as pd
import yfinance as yf
import matplotlib.pyplot as plt

# Download IBM stock data for the year 2021
start_date = '2021-01-01'
end_date = '2021-12-31'
stock_data = yf.download('IBM', start=start_date, end=end_date)

# Calculate MACD
def calculate_macd(df, short_window=12, long_window=26, signal_window=9):
    df['ShortEMA'] = df['Close'].ewm(span=short_window, adjust=False).mean()
    df['LongEMA'] = df['Close'].ewm(span=long_window, adjust=False).mean()
    df['MACD'] = df['ShortEMA'] - df['LongEMA']
    df['Signal_Line'] = df['MACD'].ewm(span=signal_window, adjust=False).mean()
    df['MACD_Histogram'] = df['MACD'] - df['Signal_Line']
    return df

stock_data = calculate_macd(stock_data)

# Create a figure with two subplots
fig, ax1 = plt.subplots(figsize=(12, 6))

# Plot stock price on primary axis
color = 'tab:blue'
ax1.set_xlabel('Date')
ax1.set_ylabel('Stock Price', color=color)
ax1.plot(stock_data.index, stock_data['Close'], label='Stock Price', color=color)
ax1.tick_params(axis='y', labelcolor=color)

# Create secondary axis for MACD
ax2 = ax1.twinx()
color = 'tab:red'
ax2.set_ylabel('MACD', color=color)
ax2.plot(stock_data.index, stock_data['MACD'], label='MACD', color=color)
ax2.plot(stock_data.index, stock_data['Signal_Line'], label='Signal Line', color='tab:green')
ax2.bar(stock_data.index, stock_data['MACD_Histogram'], label='MACD Histogram', color='gray', alpha=0.5)
ax2.tick_params(axis='y', labelcolor=color)

# Combine legends from both axes
lines_1, labels_1 = ax1.get_legend_handles_labels()
lines_2, labels_2 = ax2.get_legend_handles_labels()
lines = lines_1 + lines_2
labels = labels_1 + labels_2
ax1.legend(lines, labels, loc='upper left')

plt.title('IBM Stock Price and MACD')
plt.show()

# Create buy/sell signals based on MACD crossovers
def get_signals(df):
    signals = []
    for i in range(1, len(df)):
        if df['MACD'][i] > df['Signal_Line'][i] and df['MACD'][i - 1] <= df['Signal_Line'][i - 1]:
            signals.append((df.index[i], 'Buy'))
        elif df['MACD'][i] < df['Signal_Line'][i] and df['MACD'][i - 1] >= df['Signal_Line'][i - 1]:
            signals.append((df.index[i], 'Sell'))
        else:
            signals.append((df.index[i], 'Hold'))
    return signals

signals = get_signals(stock_data)

# Print buy/sell signals
for signal in signals:
    if signal[1] != 'Hold':
        print(f"Signal Date: {signal[0]}, Signal: {signal[1]}")
