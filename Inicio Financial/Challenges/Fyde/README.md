# Smart Beta with Momentum Capture


## Instructions and Install Packages

The Jupyter nodebook must be run under python 3.10.  Type the below commands in the Terminal to  to create and activate a conda environment.

```
conda create -n py310 python=3.10 anaconda
activate py310 #if on Windows
source activate py310 #if on Linux or MacOS
```

After that, run the main notebook `SmartBeta_withMomentum.ipynb` using the above local environment. 

## Main Files: Jupyter Structure

```
1.   Load the provided synthetic data
2.   Apply an initial selection filter to choose assets
3.   Create a market-weighted index benchmark
4.   Optimize the manager's ETF portfolio
5.   Calculate a rebalancer for the portfolio
6.   Evaluate performance using variety of metrics

```
## Data

Data table inclues 100 tokens for dates ranging from 31/12/2020 to 26/09/2023.

Columns include: date, ticker, adj_close, adj_volume, and adj_market_cap

The underlying data contains highly volatile data with some assets falling toward near zero.


See 'Fyde Algothon Intructions' for further information.