#include <iostream>
#include "Stocks.h"
#include "../Regressors/Volatility.h"
using namespace std;

int main() {
    Stock myStock("MSFT");

	cout << "Stock Price: $" << myStock.getLastPrice() << endl;
	cout << "As of " << myStock.getLastDate() << endl;
	cout << "RSI (14)" << myStock.getRSI() << endl;

	vector<double> ret = LogReturns(myStock.getPrices());
	double vol1 = realisedVol(ret)*100;
	double vol2 = bootstrapStandardDeviation(ret)*100;

	cout << "Realised Volatility: "<< vol1 << "%" << endl;
	cout << "Bootstrapped Volatility: " << vol2 << "%" << endl;

	return 0;
}