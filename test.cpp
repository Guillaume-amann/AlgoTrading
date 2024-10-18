#include <iostream>
#include "Instruments/Bonds.h"

int main() {
	Bond myBond("Cie X", 1000.0, 5.0, "2020-01-01", "2030-12-31", 1);
	double rate = 0.0325;
	double price = myBond.price(rate);	//ECB rate as of 2024-10-18 @3.25%
	std::cout << "Bond Price: $" << price << std::endl;

	return 0;
}
