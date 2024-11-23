#include <iostream>
#include <cmath>
#include "../Numeric/Distributions.h"
using namespace std;

class BSMModel {
private:
    double S, K, T, r, q, sigma;
    char optionType;

public:
    BSMModel(double S, double K, double T, double r, double q, double sigma, char optionType = 'C')
        : S(S), K(K), T(T), r(r), q(q), sigma(sigma), optionType(optionType) {}

    double price() {
        double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
        double d2 = d1 - sigma * sqrt(T);
        return (optionType == 'C') 
            ? S * exp(-q * T) * stdN(d1) - K * exp(-r * T) * stdN(d2)
            : K * exp(-r * T) * stdN(-d2) - S * exp(-q * T) * stdN(-d1);
    }
};