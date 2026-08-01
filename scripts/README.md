# Financial Library for Position Management and Analysis

This C++ project provides a financial library designed for managing and analysing financial positions, specifically focused on bonds, derivatives, and other financial instruments. The library includes a `Position` class to manage and track position attributes, calculate returns, and monitor portfolio performance.

## Features

- **Position Management**:
  - Track essential attributes like ticker, price bought, volume, and returns for each position.
  - Automatically logs daily position data in `Portfolio/Positions.csv`.
  - Initializes each `Position` object with a ticker symbol and corresponding line in `Positions.csv` for easy data parsing.
  
- **Return Calculations**:
  - The `checkPosition` method calculates the position’s length and return, offering a straightforward overview of performance.
  
- **Data Storage**:
  - Daily positions are saved in CSV format, ensuring a clear record of historical data.
  - Filename for positions is set to `Portfolio/Positions.csv` by default.

## Project Structure

- Feel free to explore the Overview.pptx that maps the architecture of the project

## Requirements

- C++ compiler (e.g., GCC)
- Standard C++ libraries
- Python 3.13
- yfinance python library

## macOS version

If on macOS and want to automate the email alerts, please use the scripts in `macOS_scripts` folder.
Place the `auto.sh` file somewhere in `Users/username/` but neither in Documents nor in Downloads as Apple tends to restrict access to these folder. THis might lead to `Unload failed: 5: Input/output error \'Try running launchctl bootout\' as root for richer errors.` in the terminal when loading the .plist with the `launchctl` command or `/bin/bash ... operation not permitted` in the error.log file if the script eventualy loads.



Vix
Gold
Spy
Eur/usd


Regime-based strategies: adjust allocations if market conditions change (volatility spikes, recession indicators, etc.).
Impulse control / stochastic control for transaction-cost-aware rebalancing. 


 then propose a list of buy sell oreders and amount of cash to deal with, rounded to the euro, based upon assumption of max 30 asset in the portfolio and 40$ to balance between each


he risk-neutral probability distribution is exactly what people mean when they say options contain a market-implied “forecast” of future prices. Below I’ll:
	1.	explain the math in plain terms,
	2.	list practical steps and pitfalls, and
	3.	give a complete, ready-to-run Python script you can use locally to extract the risk-neutral density (RND) from an option chain.

⸻

1) Intuition & math (short)
	•	Under no-arbitrage and risk-neutral pricing, the price of a European call with strike K and expiry T is:
C(K) = e^{-rT}\int_{K}^{\infty} (S_T - K)\, q(S_T)\, dS_T
where q(S_T) is the risk-neutral density of the underlying at expiry and r is the risk-free rate.
	•	Breeden & Litzenberger (1978) show:
q(K) = e^{rT}\frac{\partial^{2} C(K)}{\partial K^{2}}
(i.e., the second derivative of the call price w.r.t. strike gives the RND evaluated at K, up to the discount factor).
	•	Practically: you build a smooth function C(K) across strikes and numerically compute \partial^2 C/\partial K^2. Beware: numerical differentiation amplifies noise, so smoothing or working via an implied volatility surface is usually required.

Notes:
	•	If you only have puts or if strikes span the entire range, you can use puts (similar formula) or combine via put-call parity to align with the forward price.
	•	Use put-call parity to get the forward price F:
C(K)-P(K) = e^{-rT}(F - K)
so F can be deduced from observed option prices (choose a strike / mid of robustly priced options).


Memory management for the lib (OCaml, Assembly, C++ heap)
Reccomandation system for the lib
Content filtering (me and Antoine two filled list then only explicit a few) then apply collaborative filtering approach to approximate the elements of the recommandation matrix via by trial and errors matrix factorisation (= product of user matrix and item matrix) (with k-means? With Neural CF layers? (What are embeddings layers))
TWAV/VWAP