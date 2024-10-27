#include <iostream>
#include <vector>
#include "../Regressors/Volatility.h"
#include "Stocks.h"
using namespace std;

int main() {
    Stock myStock("AAPL");
    double stcPrice = myStock.lastPrice;

	cout << "Stock Price: $" << stcPrice << endl;
		
	return 0;
}