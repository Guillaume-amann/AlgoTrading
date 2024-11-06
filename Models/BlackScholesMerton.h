#include <iostream>
#include <cmath>
#include <complex>
#include "../Numeric/Distributions.h"
using namespace std;

class BSMModel {
private:
    double S;             // Stock price
    double K;             // Strike price
    double T;             // Time to maturity
    double r;             // Risk-free rate
    double q;             // Dividend yield
    double sigma;         // Volatility
    char optionType;      // Option type ('C' for Call, 'P' for Put)

public:
    BSMModel(double S, double K, double T, double r, double q, double sigma, char optionType = 'C')
        : S(S), K(K), T(T), r(r), q(q), sigma(sigma), optionType(optionType) {}

    double price() {
        double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
        double d2 = d1 - sigma * sqrt(T);

        if (optionType == 'C') {
            return S * exp(-q * T) * stdN(d1) - K * exp(-r * T) * stdN(d2);
        } else {
            return K * exp(-r * T) * stdN(-d2) - S * exp(-q * T) * stdN(-d1);
        }
    }
};