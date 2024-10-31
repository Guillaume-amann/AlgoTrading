#include <iostream>
#include "Stocks.h"
using namespace std;

int main() {
    Stock myStock("AAPL");

	cout << "Stock Price: $" << myStock.getLastPrice() << endl;
	cout << "As of " << myStock.getLastDate() << endl;
		
	return 0;
}