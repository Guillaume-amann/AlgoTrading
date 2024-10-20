#include <iostream>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

double bootstrap(const vector<double>& data, int num_samples) {
    int n = data.size();
    double mean = 0.0;
    for (double value : data) {
        mean += value;
    }
    mean /= n;

    vector<double> bootstrap_means;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);

    for (int i = 0; i < num_samples; ++i) {
        double sample_mean = 0.0;
        for (int j = 0; j < n; ++j) {
            sample_mean += data[dist(gen)];
        }
        sample_mean /= n;
        bootstrap_means.push_back(sample_mean);
    }

    double bootstrap_mean = 0.0;
    for (double bm : bootstrap_means) {
        bootstrap_mean += bm;
    }
    bootstrap_mean /= num_samples;

    double variance = 0.0;
    for (double bm : bootstrap_means) {
        variance += (bm - bootstrap_mean) * (bm - bootstrap_mean);
    }
    variance /= (num_samples - 1);

    return sqrt(variance);
}

double analytical(const vector<double>& data) {
    int n = data.size();
    double mean = 0.0;

    for (double value : data) {
        mean += value;
    }
    mean /= n;

    double sum_squared_error = 0.0;
    for (double value : data) {
        sum_squared_error += (value - mean) * (value - mean);
    }

    return sqrt(sum_squared_error / (n - 1));
}

double hist_vol(const vector<double>& dataVector, const string& flag, const string& method = "analytical") {
    if (flag == "y" && dataVector.size() == 252) {
        return (method == "bootstrap") ? bootstrap(dataVector, 10000) : analytical(dataVector);
    } else if (flag == "m" && dataVector.size() == 21) {
        return (method == "bootstrap") ? bootstrap(dataVector, 10000) : analytical(dataVector);
    } else {
        cerr << "Error: Invalid vector size or flag. Expected flag 'y' with size 252, or 'm' with size 21.\n";
        return -1.0;
    }
}