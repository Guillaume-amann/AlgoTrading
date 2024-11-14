#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Options.h"

using namespace std;

void processCSV(const string& filename) {
    ifstream file(filename);
    string line;
    vector<StockOption> options;
    
    // Assuming the first line is a header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string stockPriceStr, strikeStr, lastPriceStr, maturityStr;
        
        getline(ss, stockPriceStr, ',');
        getline(ss, strikeStr, ',');
        getline(ss, lastPriceStr, ',');
        getline(ss, maturityStr, ',');
        
        double stockPrice = stod(stockPriceStr);
        double strike = stod(strikeStr);
        double lastPrice = stod(lastPriceStr);
        double maturity = stod(maturityStr);
        
        // Create Option instance and calculate implied volatility
        StockOption opt(stockPrice, strike, maturity, 0.05, lastPrice);
        
        options.push_back(opt);
    }
    
    // Output results to a new CSV
    ofstream output("output.csv");
    output << "StockPrice,Strike,LastPrice,Maturity,IV\n";
    
    for (const auto& opt : options) {
        output << opt.getStockPrice() << "," << opt.getStrikePrice() << "," << opt.getlastPrice() << "," << opt.getTimeToMaturity() << "," << opt.getVolatility() << "\n";
    }
}

int main() {
    string filename = "Database/Call.csv";  // Replace with your actual file path
    processCSV(filename);
    return 0;
}