#include <iostream>
#include <cmath>
#include <fstream>
#include "../Regressors/Volatility.h"
#include "../Numeric/Distributions.h"
#include "../Models/Heston.h"
#include "../Models/BlackScholesMerton.h"
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
    string modelType;       // Model type ('BSM', 'Heston')

    double optionPrice;
    double lastPrice;       // Market Price

    // Greeks
    double deltaValue, gammaValue, vegaValue, rhoValue, thetaValue;

    double d1() const {
        return (log(stockPrice / strikePrice) + (riskFreeRate - dividendYield + 0.5 * volatility * volatility) * timeToMaturity) 
               / (volatility * sqrt(timeToMaturity));
    }

    double d2() const {
        return d1() - volatility * sqrt(timeToMaturity);
    }

public:
    StockOption(double S, double K, double T, double r, double P, char type = 'C', double q = 0.0, string model = "BSM")
        : stockPrice(S), strikePrice(K), timeToMaturity(T), riskFreeRate(r), lastPrice(P), optionType(type), dividendYield(q), modelType(model) {

        volatility = calculateImpliedVolatility(lastPrice);

        optionPrice = price();
        deltaValue = delta();
        gammaValue = gamma();
        vegaValue = vega();
        rhoValue = rho();
        thetaValue = theta();

        plotDataForPython();
    }
 
    double price() {
        if (modelType == "BSM") {
            return BSM_price(volatility);
        } else if (modelType == "Heston") {
            return Heston_price();
        } else {
            throw invalid_argument("Unsupported model type");
        }
    }

    double BSM_price(double tempVol) {
        BSMModel myModel(stockPrice, strikePrice, timeToMaturity, tempVol, riskFreeRate, dividendYield, optionType); 
        return myModel.price();
    }

    double Heston_price() {
        HestonModel myModel(stockPrice, strikePrice, timeToMaturity, riskFreeRate, dividendYield, optionType); 
        return myModel.price();
    }

    double delta() {
        if (optionType == 'C') {
            deltaValue = exp(-dividendYield * timeToMaturity) * stdN(d1());
        } else {
            deltaValue = exp(-dividendYield * timeToMaturity) * (stdN(d1()) - 1);
        }
        return deltaValue;
    }

    double gamma() {
        gammaValue = normal(d1()) * exp(-dividendYield * timeToMaturity) / (stockPrice * volatility * sqrt(timeToMaturity));
        return gammaValue;
    }

    double vega() {
        vegaValue = stockPrice * normal(d1()) * exp(-dividendYield * timeToMaturity) * sqrt(timeToMaturity);
        return vegaValue;
    }
    
    double rho() {
        if (optionType == 'C') {
            rhoValue = timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * stdN(d2());
        } else {
            rhoValue = -timeToMaturity * strikePrice * exp(-riskFreeRate * timeToMaturity) * stdN(-d2());
        }
        return rhoValue;
    }

    double theta() {
        double term1 = (-stockPrice * normal(d1()) * exp(-dividendYield * timeToMaturity) * volatility) / (2 * sqrt(timeToMaturity));
        double term2 = dividendYield * stockPrice * exp(-dividendYield * timeToMaturity) * stdN(d1());
        double term3 = riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * stdN(d2());

        if (optionType == 'C') {
            thetaValue = term1 - term2 - term3;
        } else {
            thetaValue = term1 + term2 + riskFreeRate * strikePrice * exp(-riskFreeRate * timeToMaturity) * stdN(-d2());
        }
        return thetaValue;
    }

    double calculateImpliedVolatility(double marketPrice, double tolerance = 1e-2, int maxIterations = 1000) {
        // Function pointers for BSM pricing and Vega
        std::function<double(double)> pricingFunc = std::bind(&StockOption::BSM_price, this, std::placeholders::_1);
        
        // Call the Bisection method
        double impliedVolBisection = bisectionMethod(pricingFunc, 0.001, 5.0, marketPrice, tolerance);
        cout << "Implied Volatility (Bisection): " << impliedVolBisection << endl;

        // Call the Secant method
        double impliedVolSecant = secantMethod(pricingFunc, 0.001, 0.5, marketPrice, tolerance);
        cout << "Implied Volatility (Secant): " << impliedVolSecant << endl;

        // Return the first method's result as default
        volatility = impliedVolBisection;
        return volatility;
    }

    void plotDataForPython(const string& filename = "./Database/option_data.csv") {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for plotting data.");
        }

        file << "StockPrice,StrikePrice,TimeToMaturity,ImpliedVolatility\n";
        file << stockPrice << "," << strikePrice << "," << timeToMaturity << "," << volatility << "\n";
        
        file.close();
    }

    string getStockTicker() const { return stockTicker; }
    double getStockPrice() const { return stockPrice; }
    double getStrikePrice() const { return strikePrice; }
    double getTimeToMaturity() const { return timeToMaturity; }
    double getVolatility() const { return volatility; }
    double getRiskFreeRate() const { return riskFreeRate; }
    double getDividendYield() const { return dividendYield; }
    char getOptionType() const { return optionType; }
    double getlastPrice() const { return lastPrice; }

    void displayGreeks() const {
        cout << "Delta: " << deltaValue << endl;
        cout << "Gamma: " << gammaValue << endl;
        cout << "Vega: " << vegaValue << endl;
        cout << "Rho: " << rhoValue << endl;
        cout << "Theta: " << thetaValue << endl;
    }
};