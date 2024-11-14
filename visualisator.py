import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

data = pd.read_csv("./Database/Call.csv")
strike = data['Strike'].values
implied_volatility = data['ImpliedVolatility'].values
maturity = data['Maturity'].values

# Create a grid for plotting
# We need to mesh the strike and maturity values into a 2D grid
strike_grid, maturity_grid = np.meshgrid(np.unique(strike), np.unique(maturity))

# Create an array for the implied volatility on the grid
implied_volatility_grid = np.zeros(strike_grid.shape)

# Fill in the implied_volatility_grid with the corresponding values
for i in range(len(strike)):
    # Find the row in the grid
    strike_idx = np.where(strike_grid == strike[i])[1][0]
    maturity_idx = np.where(maturity_grid == maturity[i])[0][0]
    implied_volatility_grid[maturity_idx, strike_idx] = implied_volatility[i]

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(strike_grid, maturity_grid, implied_volatility_grid, cmap='viridis')
ax.set_xlabel('Strike Price')
ax.set_ylabel('Maturity (Years)')
ax.set_zlabel('Implied Volatility')
ax.set_title('Implied Volatility vs. Strike Price and Maturity')
fig.colorbar(surf, label='Implied Volatility')
plt.show()