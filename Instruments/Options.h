#include <iostream>
#include <cmath>
using namespace std;

class StockOption {
private:
    double stockPrice;      // Current stock price (S)
    double strikePrice;     // Strike price of the option (K)
    double timeToMaturity;  // Time to maturity (T) in years
    double volatility;      // Volatility (sigma) in %
    double riskFreeRate;    // Risk-free interest rate (r) in %
    double dividendYield;   // Dividend yield (q)
    string optionType;        // Option type ('C' for Call, 'P' for Put)

    // Standard normal cumulative distribution function
    double N(double x) const {
        return 0.5 * (1.0 + erf(x / sqrt(2.0)));
    }

    // Normal density function
    double f(double x) const {
        return exp(-x * x * 0.5) / sqrt(2 * 3.141592);
    }

    double d1() const {
        return (log(stockPrice / strikePrice) + (riskFreeRate - dividendYield + 0.5 * volatility * volatility) * timeToMaturity) 
               / (volatility * sqrt(timeToMaturity));
    }

    double d2() const {
        return d1() - volatility * sqrt(timeToMaturity);
    }

public:
    StockOption(double S, double K, double T, double sigma, double r, double q = 0.0, string type)
        : stockPrice(S), strikePrice(K), timeToMaturity(T), volatility(sigma), riskFreeRate(r), dividendYield(q), optionType(type) {}

    double price() const {
        if (optionType == 'C') {
            return stockPrice * exp(-dividendYield * timeToMaturity) * N(d1()) - 
                   strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2());
        } 
        else {
            return strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2()) - 
                   stockPrice * exp(-dividendYield * timeToMaturity) * N(-d1());
        }
    }

    double delta() const {
        if (optionType == 'C')
            return exp(-dividendYield * timeToMaturity) * N(d1());
        else
            return exp(-dividendYield * timeToMaturity) * (N(d1()) - 1);
    }

    double gamma() const {
        return f(d1()) * exp(-dividendYield * timeToMaturity) / (stockPrice * volatility * sqrt(timeToMaturity));
    }

    double vega() const {
        return stockPrice * f(d1()) * exp(-dividendYield * timeToMaturity) * sqrt(timeToMaturity);
    }

    double rho() const {
        if (optionType == 'C')
            return timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2());
        else
            return -timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2());
    }

    double theta() const {
        double term1 = (-stockPrice * f(d1()) * exp(-dividendYield * timeToMaturity) * volatility) / (2 * sqrt(timeToMaturity));
        double term2 = dividendYield * stockPrice * exp(-dividendYield * timeToMaturity) * N(d1());
        double term3 = riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2());

        if (optionType == 'C')
            return term1 - term2 - term3;
        else
            return term1 + term2 + riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2());
    }
};