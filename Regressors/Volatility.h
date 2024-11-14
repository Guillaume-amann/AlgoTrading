#include <iostream>
#include <numeric>
#include <random>
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

    std::vector<double> sample;
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