#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <Eigen/Dense>  // For matrix operations

using namespace std;
using namespace Eigen;

class Portfolio {
private:
    vector<string> stocks;
    vector<double> stocksReturns;
    vector<double> portReturns;
    vector<double> weights;
    string filename = "/Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/Database/Universe.csv";  // Default file location for tickers
    double hvar;

    // Helper function to read tickers from a CSV file
    vector<string> readTickers(const string& filename) {
        ifstream file(filename);
        vector<string> tickers;
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ticker;
                while (getline(ss, ticker, ',')) {
                    tickers.push_back(ticker);
                }
            }
            file.close();
        } else {
            cerr << "Error opening file: " << filename << endl;
        }
        return tickers;
    }

public:
    Portfolio() : hvar(0.0) { stocks = readTickers(filename); }

    // Generates random weights for the portfolio and scales them to 100%
    void generateRandomWeights(int num_assets) {
        weights.resize(num_assets);
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);

        for (int i = 0; i < num_assets; ++i) {
            weights[i] = dis(gen);
        }
        double sum_weights = accumulate(weights.begin(), weights.end(), 0.0);
        for (auto& weight : weights) {
            weight /= sum_weights;
            weight *= 100;  // Scale to percentage
        }
    }

    tuple<double, double, double> calculatePortfolioMetrics(const VectorXd& returns, const MatrixXd& cov_mat, double time) {
        int num_assets = cov_mat.rows();
        VectorXd eigen_weights = VectorXd::Map(weights.data(), num_assets);

        double portfolio_return = eigen_weights.dot(returns / 100);
        double portfolio_variance = eigen_weights.transpose() * cov_mat * eigen_weights;
        double portfolio_vol = sqrt(portfolio_variance * sqrt(time));
        double sharpe = round((portfolio_return - 5.33) / portfolio_vol * 1000) / 1000.0;

        return make_tuple(portfolio_return, portfolio_vol, sharpe);
    }

    void setStocksReturns(const vector<double>& newStocksReturns) {
        stocksReturns = newStocksReturns;
    }

    void setPortReturns(const vector<double>& newPortReturns) {
        portReturns = newPortReturns;
    }

    // Historical Value at Risk (hVaR)
    void calculateVaR(const VectorXd& portfolio_returns, int alpha=5) {
        vector<double> returns_vec(portfolio_returns.data(), portfolio_returns.data() + portfolio_returns.size());
        sort(returns_vec.begin(), returns_vec.end());
        int index = static_cast<int>((alpha / 100.0) * returns_vec.size());
        hvar = -returns_vec[index] / 100;
    }

    vector<string> getStocks() { return stocks; }
    vector<double> getStocksReturns() { return stocksReturns; }
    vector<double> getPortReturns() { return portReturns; }
    vector<double> getWeights() { return weights; }
    double getVaR() { return hvar; }
};