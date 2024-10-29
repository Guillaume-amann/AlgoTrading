#include <iostream>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

double ISL_bootstrap(const vector<double>& data, int num_samples) {
    int n = data.size();
    double mean = accumulate(data.begin(), data.end(), 0.0) / n;

    vector<double> bootstrap_means(num_samples);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);

    for (int i = 0; i < num_samples; ++i) {
        double sample_mean = 0.0;
        for (int j = 0; j < n; ++j) {
            sample_mean += data[dist(gen)];
        }
        bootstrap_means[i] = sample_mean / n;
    }

    double bootstrap_mean = accumulate(bootstrap_means.begin(), bootstrap_means.end(), 0.0) / num_samples;
    double variance = accumulate(bootstrap_means.begin(), bootstrap_means.end(), 0.0, [bootstrap_mean](double acc, double bm) 
                        {return acc + (bm - bootstrap_mean) * (bm - bootstrap_mean);}) / (num_samples - 1);
    return sqrt(variance);
}

double analytical(const vector<double>& data) {
    int n = data.size();
    double mean = accumulate(data.begin(), data.end(), 0.0) / n;
    double sum_squared_error = accumulate(data.begin(), data.end(), 0.0, [mean](double acc, double value) 
                        {return acc + (value - mean) * (value - mean);});
    return sqrt(sum_squared_error / (n - 1));
}

double hist_vol(const vector<double>& priceHistory, const string& TimePeriod, const string& method = "analytical") {
    if (TimePeriod == "y" && priceHistory.size() == 252) {
        return (method == "bootstrap") ? ISL_bootstrap(priceHistory, 10000) : analytical(priceHistory);
    } else if (TimePeriod == "m" && priceHistory.size() == 21) {
        return (method == "bootstrap") ? ISL_bootstrap(priceHistory, 10000) : analytical(priceHistory);
    } else {
        cerr << "Error: Invalid vector size or TimePeriod. Expected TimePeriod 'y' with size 252, or 'm' with size 21.\n";
        return -1.0;
    }
}