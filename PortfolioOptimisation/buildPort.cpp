#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "MPT.h"
using namespace std;

int main() {
    Portfolio myPortfolio;
    double invest = 1000;
    vector<string> tickers = myPortfolio.getStocks();
    for (string ticker : tickers) {
        cout << ticker << " ";
    }


    // myPortfolio.calculateVaR(portfolio_returns, alpha);
    // double historical_VaR = myPortfolio.getVaR();  // Correct call

    // cout << "\nExpected Return: " << get<0>(metrics) << "%\n";
    // cout << "Value at Risk 95%: $" << (historical_VaR * invest) << "\n";

    return 0;
}