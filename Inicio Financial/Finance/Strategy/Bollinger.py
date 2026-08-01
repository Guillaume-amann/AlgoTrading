import numpy as np
import pandas as pd
import yfinance as yf
import matplotlib.pyplot as plt

SNP = yf.download('^GSPC', '2021-01-01', '2023-01-01')

# Define ranges for span and z_val
span_range = range(15, 100, 2)  # Testing span from 5 to 30 in steps of 5
z_val_range = np.arange(0, 5, 0.1)  # Testing z_val from 1.5 to 2.5 in steps of 0.1

best_combinations = []
top_n = 2  # Top 2 combinations

for span in span_range:
    for z_val in z_val_range:
        stock = SNP.copy()

        stock['mean'] = stock['Adj Close'].ewm(span=span).mean()
        stock['std'] = stock['Adj Close'].ewm(span=span).std()

        stock.dropna(inplace=True)

        stock['upper_b'] = stock['mean'] + z_val * stock['std']
        stock['lower_b'] = stock['mean'] - z_val * stock['std']

        long = stock['Adj Close'] <= stock['lower_b']
        short = stock['Adj Close'] >= stock['upper_b']

        stock['position'] = np.nan
        stock.loc[long, 'position'] = 1
        stock.loc[short, 'position'] = -1
        stock['position'].fillna(inplace=True, method='ffill')

        stock['log_returns'] = np.log(stock['Adj Close'] / stock['Adj Close'].shift(1))
        stock['strategy_returns'] = stock['log_returns'] * (-1 * stock['position'].shift(1))

        # Calculate cumulative strategy returns
        cumulative_strategy_returns = stock['strategy_returns'].cumsum()

        # Record the final cumulative return
        final_return = cumulative_strategy_returns.iloc[-1]

        # Check if final return is a valid float
        if isinstance(final_return, float):
            # Add the combination and its final return to the list
            best_combinations.append((span, z_val, final_return))

# Sort the combinations by final return in descending order
best_combinations.sort(key=lambda x: x[2], reverse=True)

# Filter out combinations with NaN returns
best_combinations = [comb for comb in best_combinations if not np.isnan(comb[2])]

# Print the top 2 combinations
for i in range(min(top_n, len(best_combinations))):
    span, z_val, final_return = best_combinations[i]
    print(f"Top {i+1} Combination - Span: {span}, z_val: {z_val}, Final Return: {final_return:.2%}")

# Plot the top performing combination
best_span, best_z_val, _ = best_combinations[0]
stock = SNP.copy()

stock['mean'] = stock['Adj Close'].ewm(span=best_span).mean()
stock['std'] = stock['Adj Close'].ewm(span=best_span).std()

stock.dropna(inplace=True)

stock['upper_b'] = stock['mean'] + best_z_val * stock['std']
stock['lower_b'] = stock['mean'] - best_z_val * stock['std']

long = stock['Adj Close'] <= stock['lower_b']
short = stock['Adj Close'] >= stock['upper_b']

stock['position'] = np.nan
stock.loc[long, 'position'] = 1
stock.loc[short, 'position'] = -1
stock['position'].fillna(inplace=True, method='ffill')

fig, ax1 = plt.subplots(figsize=(10,5))
ax1.plot(stock['Adj Close'], label='SNP 500', color='blue')
ax1.plot(stock['mean'], label=f'EMA {best_span}', color='lightblue')
ax1.plot(stock['upper_b'], label='upper BB', color='grey', linestyle='--')
ax1.plot(stock['lower_b'], label='lower BB', color='grey', linestyle='--')

plt.legend()
ax2 = ax1.twinx()
ax2.plot(stock['position'], label='position', color='red')
plt.title("Best Bollinger Band Mean Reversion Strategy")
plt.show()


SNP['log_returns'] = np.log(SNP['Adj Close'] / SNP['Adj Close'].shift(1))
SNP['cumulative_returns'] = SNP['log_returns'].cumsum()

stock['log_returns'] = np.log(stock['Adj Close'] / stock['Adj Close'].shift(1))
stock['strategy_returns'] = stock['log_returns'] * (-1 * stock['position'].shift(1))

fig, ax = plt.subplots(figsize=(10, 5))
ax.plot(SNP['cumulative_returns'], label='SNP 500 Returns', color='blue')
ax.plot(stock['strategy_returns'].cumsum(), label='Strategy Returns', color='green')

result = (stock['strategy_returns'].cumsum())[-1]

# Annotate the last point of the strategy returns
ax.annotate(f'({result:.2%})',
            xy=(stock.index[-1], stock['strategy_returns'].cumsum().iloc[-1]),
            xytext=(-20, 20), textcoords='offset points',
            arrowprops=dict(facecolor='black', arrowstyle='->'))

plt.title('Cumulative Returns Comparison')
plt.xlabel('Date')
plt.ylabel('Cumulative Returns')
plt.legend()
plt.show()