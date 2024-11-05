#include <iostream>
using namespace std;

class Portfolio {
private:
    vector<string> stocks;
    vector<double> stocksReturns;
    vector<double> portReturns;
    vector<double> weights;

public:
    vector<string> getStocks() { return stocks; };
    vector<double> getStocksReturns() { return stocksReturns; }; 
    vector<double> getPortReturns() { return portReturns; };
    vector<double> getWeights() { return weights; };
}