#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

class HestonModel {
private:
    double kappa;         // Rate of mean reversion
    double theta;         // Long-run variance
    double sigma_v;       // Volatility of volatility
    double rho;           // Correlation between asset price and volatility

    double S;             // Stock price
    double K;             // Strike price
    double T;             // Time to maturity
    double r;             // Risk-free rate
    double q;             // Dividend yield
    char optionType;      // 'C' for Call, 'P' for Put

    complex<double> calculateHestonCharacteristicFunction(double k) {
        complex<double> i(0, 1);  // Imaginary unit
        complex<double> characteristicFunction = exp(i * k * log(S) + i * k * (log(K) - log(S)) - 0.5 * k * k * theta * T);
        return characteristicFunction;
    }

public:
    HestonModel(double S, double K, double T, double r, double q, char optionType,
                    double kappa = 2.0, double theta = 0.04, double sigma_v = 0.1, double rho = -0.5)
                : S(S), K(K), T(T), r(r), q(q), optionType(optionType),
                    kappa(kappa), theta(theta), sigma_v(sigma_v), rho(rho) {}

    double price(int N = 100, double lambda = 0.1) {
        // Numerical integration parameters (e.g., Fourier transform parameters)
        complex<double> sum(0.0, 0.0); // Sum for Fourier transform
        
        for (int i = 0; i < N; ++i) {
            double k = i * lambda;
            complex<double> complexTerm = calculateHestonCharacteristicFunction(k);
            sum += complexTerm;
        }
    
        // Apply inverse Fourier transform (simplified)
        double realPrice = exp(-r * T) * real(sum);

        if (optionType == 'C') {  // Call option
            return realPrice;
        } else if (optionType == 'P') {  // Put option
            return realPrice - S + K * exp(-r * T);
        } else {
            cerr << "Invalid option type specified. Use 'C' for Call or 'P' for Put." << endl;
            return 0.0;
        }
    }
};