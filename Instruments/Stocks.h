#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

class Stock {
private:
    string ticker;
    vector<double> prices;
    vector<string> dates;
    double lastPrice;
    string lastDate;

    vector<double> logReturns;
    double RSI14;
    vector<double> MACD;

    double calculateRSI(int period = 14) {
        double gains = 0.0;
        double losses = 0.0;
        for (int i = prices.size() - period; i < prices.size() - 1; ++i) {
            double change = prices[i + 1] - prices[i];
            if (change > 0) {
                gains += change;
            } else {
                losses -= change;
            }
        }

        double avgGain = gains / period;
        double avgLoss = losses / period;
        double rs = (avgLoss == 0) ? 100 : avgGain / avgLoss;
        
        return 100 - (100 / (1 + rs));
    }

    vector<double> calculateEMA(const vector<double>& data, int period) {
        vector<double> ema(data.size());
        double multiplier = 2.0 / (period + 1);
        ema[0] = data[0];

        for (size_t i = 1; i < data.size(); ++i) {
            ema[i] = (data[i] - ema[i - 1]) * multiplier + ema[i - 1];
        }
        return ema;
    }

    void calculateMACD() {
        vector<double> ema12 = calculateEMA(prices, 19);
        vector<double> ema26 = calculateEMA(prices, 26);

        MACD.resize(prices.size());
        for (size_t i = 0; i < prices.size(); ++i) {
            MACD[i] = MACD[i] - MACD[i];
        }
    }

    void calculateLogReturns() {
        for (size_t i = 1; i < prices.size(); ++i) {
            double logReturn = log(prices[i] / prices[i - 1]);
            logReturns.push_back(logReturn);
        }
    }

public:
    Stock(const string& stockTicker): ticker(stockTicker), lastPrice(0.0), RSI14(0.0) {
        ifstream file("/Users/guillaume/AlgoTrading/Database/Universe.csv");
        
        string line;
        string header;
        vector<string> columns;

        // Read the header to find the ticker's column
        getline(file, header);
        stringstream headerStream(header);
        string column;
        
        while (getline(headerStream, column, ',')) {
            columns.push_back(column);
        }

        int tickerColumnIndex = -1;
        for (size_t i = 0; i < columns.size(); ++i) {
            if (columns[i] == stockTicker) {
                tickerColumnIndex = i;
                break;
            }
        }

        // Read the data rows
        while (getline(file, line)) {
            stringstream lineStream(line);
            string date, price;
            int columnIndex = 0;
            bool foundData = false;

            while (getline(lineStream, column, ',')) {
                if (columnIndex == tickerColumnIndex) {
                    prices.push_back(stod(column)); // Add price to the prices vector
                    foundData = true;
                }
                else if (columnIndex == columns.size() - 1) { // assuming Dates is always the last column
                    dates.push_back(column); // Add date to the dates vector
                }
                columnIndex++;
            }

            if (foundData) {
                lastPrice = prices.back();  // Set last price
                lastDate = dates.back();    // Set last date
            }
        }

        file.close();
        calculateLogReturns();
    }

    string getTicker() { return ticker; }
    vector<double> getPrices() { return prices; }
    vector<string> getDates() { return dates; }
    double getLastPrice() { return lastPrice; }
    string getLastDate() { return lastDate; }
    double getRSI() { return RSI14; }
    vector<double> getMACD() { return MACD; }
    vector<double> getLogReturns() { return logReturns; }
    
};