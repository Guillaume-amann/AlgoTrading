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


## macOS version

If on macOS and want to automate the email alerts, please use the scripts in `macOS_scripts` folder.
Place the `auto.sh` file somewhere in `Users/username/` but neither in Documents nor in Downloads as Apple tends to restrict access to these folder. THis might lead to `Unload failed: 5: Input/output error \'Try running launchctl bootout\' as root for richer errors.` in the terminal when loading the .plist with the `launchctl` command or `/bin/bash ... operation not permitted` in the error.log file if the script eventualy loads.
