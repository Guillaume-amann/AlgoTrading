#include <iostream>
#include "Bonds.h"
using namespace std;

int main() {
	Bond myBond("Cie X", 1000.0, 5.0, "2020-01-01", "2030-12-31", 1);
	double rate = 0.0325;
	double Bprice = myBond.price(rate);	//ECB rate as of 2024-10-18 @3.25%

	cout << "Bond Price: $" << Bprice << endl;
	cout << "Bond yield: " << myBond.bondYield << "%" << endl;
	
	return 0;
}
