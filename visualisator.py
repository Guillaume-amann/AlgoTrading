import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("/Database/option_data.csv")

# Plot
plt.scatter(data['StrikePrice'], data['ImpliedVolatility'], c=data['ImpliedVolatility'], cmap='viridis')
plt.xlabel('Strike Price')
plt.ylabel('Implied Volatility')
plt.title('Implied Volatility vs. Strike Price')
plt.colorbar(label='Implied Volatility')
plt.show()