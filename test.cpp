#include <iostream>
#include "Instruments/Bonds.h"
#include "Instruments/Options.h"

int main() {
	Bond myBond("Cie X", 1000.0, 5.0, "2020-01-01", "2030-12-31", 1);
	double rate = 0.0325;
	double price = myBond.price(rate);	//ECB rate as of 2024-10-18 @3.25%
	std::cout << "Bond Price: $" << price << std::endl;

	double S = 100.0;  // Stock Price
	double K = 100.0;  // Strike Price
	double T = 1;  // Years to maturity
	double r = 0.05;  // Risk free interest rate
	double q = 0.0;
	double v = 0.20;  // Yearly volatility
	char OpType = 'P';  // 'C'all or 'P'ut
	std::cout << "Black Scholes Price " << BSPrice(S, K, T, r, q, v, OpType) << std::endl;
	std::cout << "Black Scholes Delta " << BSDelta(S, K, T, r, q, v, OpType) << std::endl;
	std::cout << "Black Scholes Gamma " << BSGamma(S, K, T, r, q, v) << std::endl;
	std::cout << "Black Scholes Vega  " << BSVega(S, K, T, r, q, v) << std::endl;
	std::cout << "Black Scholes Rho   " << BSRho(S, K, T, r, q, v, OpType) << std::endl;
	std::cout << "Black Scholes Theta " << BSTheta(S, K, T, r, q, v, OpType) << " per year, or " << BSTheta(S, K, T, r, q, v, OpType) / 365.0 << " per day." << endl;

	return 0;
}
