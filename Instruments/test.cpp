#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Options.h"

using namespace std;

// Helper function to read CSV data into a vector of vectors (each row as a vector)
vector<vector<string>> readCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename);
    }

    vector<vector<string>> data;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        
        while (getline(ss, value, ',')) {
            row.push_back(value);
        }
        
        data.push_back(row);
    }
    
    file.close();
    return data;
}

// Helper function to write data to CSV
void writeCSV(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing: " + filename);
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

int main() {
    vector<vector<string>> data = readCSV("./Database/Call.csv");

    // Step 2: Process each row (skip the header row)
    for (size_t i = 1; i < data.size(); ++i) {
        // Extract stock data from the row (assuming CSV columns are: StockPrice, StrikePrice, OptionPrice, TimeToMaturity)
        double stockPrice = stod(data[i][0]);    // Convert Stock Price from string to double
        double strikePrice = stod(data[i][1]);   // Convert Strike Price from string to double
        double optionPrice = stod(data[i][2]);   // Convert Option Price from string to double   
        double timeToMaturity = stod(data[i][3]); // Convert Time to Maturity from string to double


        double riskFreeRate = 0.05;  // Example risk-free rate (5%)
        double dividendYield = 0.02; // Example dividend yield (2%)
        
        // Step 3: Create StockOption object
        StockOption oneOption(stockPrice, strikePrice, timeToMaturity, 0.2, riskFreeRate, dividendYield, 'C');
        
        // Calculate Implied Volatility based on the option's market price
        double impliedVolatility = oneOption.calculateImpliedVolatility(oneOption.price());
        
        // Step 4: Add Implied Volatility to the row
        data[i].push_back(to_string(impliedVolatility));  // Add IV to the end of the row
    }

    writeCSV("./Database/Call.csv", data);
    cout << "Implied Volatility calculation completed and saved to option_data.csv!" << endl;
    return 0;
}