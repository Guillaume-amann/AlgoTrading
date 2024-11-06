#include <iostream>
#include <cmath>
using namespace std;

class StockOption {
private:
    string stockTicker;     // Ticker of the underlying
    double stockPrice;      // Current stock price (S)
    double strikePrice;     // Strike price of the option (K)
    double timeToMaturity;  // Time to maturity (T) in years
    double volatility;      // Volatility (sigma) in %
    double riskFreeRate;    // Risk-free interest rate (r) in %
    double dividendYield;   // Dividend yield (q)
    char optionType;        // Option type ('C' for call, 'P' for put)

    // Greeks
    double deltaValue, gammaValue, vegaValue, rhoValue, thetaValue;

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
    StockOption(double S, double K, double T, double sigma, double r, char type = 'C', double q = 0.0)
        : stockPrice(S), strikePrice(K), timeToMaturity(T), volatility(sigma), riskFreeRate(r), optionType(type), dividendYield(q) {}
 
    double price() {

        delta();
        gamma();
        vega();
        rho();
        theta();

        if (optionType == 'C') {
            return stockPrice * exp(-dividendYield * timeToMaturity) * N(d1()) - 
                   strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2());
        } 
        else {
            return strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2()) - 
                   stockPrice * exp(-dividendYield * timeToMaturity) * N(-d1());
        }
    }

    double delta() {
        if (optionType == 'C') {
            deltaValue = exp(-dividendYield * timeToMaturity) * N(d1());
        } else {
            deltaValue = exp(-dividendYield * timeToMaturity) * (N(d1()) - 1);
        }
        return deltaValue;
    }

    double gamma() {
        gammaValue = f(d1()) * exp(-dividendYield * timeToMaturity) / (stockPrice * volatility * sqrt(timeToMaturity));
        return gammaValue;
    }

    double vega() {
        vegaValue = stockPrice * f(d1()) * exp(-dividendYield * timeToMaturity) * sqrt(timeToMaturity);
        return vegaValue;
    }

    double rho() {
        rhoValue = (optionType == 'C') ? 
            timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2()) : 
            -timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2());
        return rhoValue;
    }

    double theta() {
        double term1 = (-stockPrice * f(d1()) * exp(-dividendYield * timeToMaturity) * volatility) / (2 * sqrt(timeToMaturity));
        double term2 = dividendYield * stockPrice * exp(-dividendYield * timeToMaturity) * N(d1());
        double term3 = riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(d2());

        thetaValue = (optionType == 'C') ? 
            term1 - term2 - term3 : 
            term1 + term2 + riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * N(-d2());
        return thetaValue;
    }

    string getStockTicker() const { return stockTicker; };     
    double getStockPrice() const { return stockPrice; };
    double getStrikePrice() const { return strikePrice; };
    double getTimeToMaturity() const { return timeToMaturity; };
    double getVolatility() const { return volatility; };
    double getRiskFreeRate() const { return riskFreeRate; };
    double getDividendYield() const { return dividendYield; };
    char getOptionType() const { return optionType; };

    void displayGreeks() const {
        cout << "Delta: " << deltaValue << endl;
        cout << "Gamma: " << gammaValue << endl;
        cout << "Vega: " << vegaValue << endl;
        cout << "Rho: " << rhoValue << endl;
        cout << "Theta: " << thetaValue << endl;
    }
};