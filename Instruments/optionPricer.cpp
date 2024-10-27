#include <iostream>
#include "Options.h"
using namespace std;

int main() {
	double S = 100.0;  // Stock Price S
	double K = 100.0;  // Strike Price K
	double T = 1;  // Years to maturity
	double v = 0.20;  // Yearly volatility in %
	double rate = 0.0325;

	StockOption call(S, K, T, v, rate, 'C');
	StockOption put(S, K, T, v, rate, 'P');
	double Cprice = call.price();
	double Pprice = put.price();

	cout << "Call Option Price: $" << Cprice << endl;
	cout << "Put Option Price: $" << Pprice << endl;
	cout << "Call Delta: " << call.delta() << endl;
	cout << "Call Gamma: " << call.gamma() << endl;
	cout << "Call Vega:  " << call.vega() << endl;
	cout << "Call Rho:   " << call.rho() << endl;
	cout << "Call Theta: " << call.theta() << " per year, or " << call.theta() / 365.0 << " per day." << endl;

	return 0;
}
