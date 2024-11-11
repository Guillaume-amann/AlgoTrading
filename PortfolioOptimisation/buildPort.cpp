#include <iostream>
#include "MPT.h"
using namespace std;

int main() {
    Portfolio myPortfolio();

    int num_assets = tickers.size();
    VectorXd annualised_returns(num_assets);
    MatrixXd cov_matrix(num_assets, num_assets);

    // Example: Populate `annualised_returns` and `cov_matrix` with data fetched by YTD(ticker)
    // Call YTD function here to fill in `annualised_returns` and `cov_matrix`

    double nb_days = 252;  // Example for a full year
    double nb_y = nb_days / 252.0;

    // Generate random weights for the portfolio and calculate metrics
    portfolio.generateRandomWeights(num_assets);
    auto metrics = portfolio.calculatePortfolioMetrics(annualised_returns, cov_matrix, nb_days);

    cout << "\nMax Sharpe Ratio: " << get<2>(metrics) << "\n\nWeights associated with Max Sharpe Portfolio:\n";
    cout << fixed << setprecision(3);
    for (int i = 0; i < num_assets; ++i) {
        cout << "Ticker " << tickers[i] << ": " << portfolio.getWeights()[i] << "%" << endl;
    }

    // Historical VaR
    double invest = 1000;
    int alpha = 5;
    VectorXd portfolio_returns; // Replace with actual data
    double historical_VaR = var_hist(portfolio_returns, alpha);

    cout << "\nExpected Return: " << get<0>(metrics) << "%\n";
    cout << "Value at Risk " << 100 - alpha << "%: $" << (historical_VaR * invest) << "\n";

    return 0;
}