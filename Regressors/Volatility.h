#include <iostream>
#include <numeric>
#include <random>
#include <cmath>
#include <stdexcept>
#include <functional>
using namespace std;

double realisedVol(const vector<double>& data, const string& type = "population") {
    int n = data.size();
    double mean = accumulate(data.begin(), data.end(), 0.0) / n;
    double sum_squared_error = accumulate(data.begin(), data.end(), 0.0, [mean](double acc, double value) 
                        {return acc + (value - mean) * (value - mean);});
    if (type != "population") {
        return sqrt(sum_squared_error / (n - 1));  // Sample standard deviation
    } else {
        return sqrt(sum_squared_error / n);  // Default to Population standard deviation
    }
}

// Function to generate a bootstrap sample from the original data
vector<double> generateBootstrapSample(const vector<double>& data) {
    int n = data.size();
    double mean = accumulate(data.begin(), data.end(), 0.0) / n;
    double stdDev = realisedVol(data);  // Use realized volatility as the standard deviation

    vector<double> sample;
    sample.reserve(n);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> normal_dist(mean, stdDev);

    // Generate normally distributed samples
    for (size_t i = 0; i < n; ++i) {
        sample.push_back(normal_dist(gen));
    }

    return sample;
}

// Function to calculate the bootstrapped standard deviation
double bootstrapStandardDeviation(const vector<double>& data, int numSamples=10000) {
    vector<double> bootstrappedStdDevs;
    for (int i = 0; i < numSamples; ++i) {
        vector<double> sample = generateBootstrapSample(data);
        double stdDev = realisedVol(sample);
        bootstrappedStdDevs.push_back(stdDev);
    }
    double mean = std::accumulate(bootstrappedStdDevs.begin(), bootstrappedStdDevs.end(), 0.0) / bootstrappedStdDevs.size();
    return mean;
}

// Bisection Method
double bisectionMethod(function<double(double)> f, double lowerBound, double upperBound, double tolerance = 1e-6, int maxIterations = 100) {
    if (f(lowerBound) * f(upperBound) > 0) {
        throw invalid_argument("Function values at the bounds must have opposite signs.");
    }

    double midPoint;
    for (int i = 0; i < maxIterations; ++i) {
        midPoint = (lowerBound + upperBound) / 2.0;
        double fMid = f(midPoint);

        if (fabs(fMid) < tolerance || (upperBound - lowerBound) / 2.0 < tolerance) {
            return midPoint;
        }

        if (fMid * f(lowerBound) < 0) {
            upperBound = midPoint;
        } else {
            lowerBound = midPoint;
        }
    }
    throw runtime_error("Bisection method did not converge within the maximum number of iterations.");
}

// Secant Method
double secantMethod(std::function<double(double)> f, double x0, double x1, double tolerance = 1e-6, int maxIterations = 100) {
    for (int i = 0; i < maxIterations; ++i) {
        double fx0 = f(x0);
        double fx1 = f(x1);

        if (std::fabs(fx1 - fx0) < 1e-10) {
            throw runtime_error("Division by near-zero value in the Secant method.");
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if (fabs(x2 - x1) < tolerance) {
            return x2;
        }

        x0 = x1;
        x1 = x2;
    }
    throw runtime_error("Secant method did not converge within the maximum number of iterations.");
}

// Brent's Method
double brentMethod(std::function<double(double)> f, double lowerBound, double upperBound, double tolerance = 1e-6, int maxIterations = 100) {
    if (f(lowerBound) * f(upperBound) > 0) {
        throw invalid_argument("Function values at the bounds must have opposite signs.");
    }

    double a = lowerBound;
    double b = upperBound;
    double c = a;
    double fa = f(a);
    double fb = f(b);
    double fc = fa;

    bool mflag = true;
    double s = b;
    double d = 0;

    for (int i = 0; i < maxIterations; ++i) {
        if (fabs(fb) < fabs(fa)) {
            swap(a, b);
            swap(fa, fb);
        }

        if (fabs(fb) < tolerance) {
            return b;
        }

        if (fabs(b - a) < tolerance) {
            return b;
        }

        if (fa != fc && fb != fc) {
            // Inverse quadratic interpolation
            s = a * fb * fc / ((fa - fb) * (fa - fc)) +
                b * fa * fc / ((fb - fa) * (fb - fc)) +
                c * fa * fb / ((fc - fa) * (fc - fb));
        } else {
            // Secant method
            s = b - fb * (b - a) / (fb - fa);
        }

        double condition1 = (s < (3 * a + b) / 4 || s > b);
        double condition2 = (mflag && fabs(s - b) >= fabs(b - c) / 2);
        double condition3 = (!mflag && fabs(s - b) >= fabs(c - d) / 2);
        double condition4 = (mflag && fabs(b - c) < tolerance);
        double condition5 = (!mflag && fabs(c - d) < tolerance);

        if (condition1 || condition2 || condition3 || condition4 || condition5) {
            s = (a + b) / 2;
            mflag = true;
        } else {
            mflag = false;
        }

        double fs = f(s);
        d = c;
        c = b;

        if (fa * fs < 0) {
            b = s;
            fb = fs;
        } else {
            a = s;
            fa = fs;
        }

        if (fabs(fa) < fabs(fb)) {
            swap(a, b);
            swap(fa, fb);
        }
    }
    throw runtime_error("Brent's method did not converge within the maximum number of iterations.");
}