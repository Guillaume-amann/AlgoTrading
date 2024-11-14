#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Options.h"

using namespace std;

// Helper function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void processCSV(const string& filename) {
    ifstream file(filename);
    string line;
    vector<StockOption> options;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string stockPriceStr, strikeStr, lastPriceStr, maturityStr;
        
        getline(ss, stockPriceStr, ',');
        getline(ss, strikeStr, ',');
        getline(ss, lastPriceStr, ',');
        getline(ss, maturityStr, ',');

        // Debugging: print maturityStr to check its format
        cout << "Parsing line: " << line << " | Maturity: " << maturityStr << endl;

        try {
            double stockPrice = stod(stockPriceStr);
            double strike = stod(strikeStr);
            double lastPrice = stod(lastPriceStr);
            double maturity = stod(maturityStr);  // Fails if maturityStr is not numeric

            StockOption opt(stockPrice, strike, maturity, 0.05, lastPrice);
            options.push_back(opt);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << "number format: " << line << endl;
            continue;
        }
    }

    // Output results to a new CSV
    ofstream output("output.csv");
    if (!output.is_open()) {
        cerr << "Error: Unable to create output file." << endl;
        return;
    }

    output << "StockPrice,Strike,LastPrice,Maturity,IV\n";
    for (const auto& opt : options) {
        output << opt.getStockPrice() << "," << opt.getStrikePrice() << "," << opt.getlastPrice() << ","
               << opt.getTimeToMaturity() << "," << opt.getVolatility() << "\n";
    }
}

int main() {
    string filename = "Database/Call.csv";  // Replace with your actual file path
    processCSV(filename);
    return 0;
}