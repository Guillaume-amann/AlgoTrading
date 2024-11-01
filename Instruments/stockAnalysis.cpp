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
	double vol1 = realisedVol(ret);
	double vol2 = ISL_bootstrap(ret);

	cout << vol1 << "     " << vol2;

	return 0;
}