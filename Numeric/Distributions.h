#include <iostream>
using namespace std;

// Standard normal cumulative distribution function
double stdN(double x) const {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

// Normal density function
double normal(double x) const {
    return exp(-x * x * 0.5) / sqrt(2 * 3.141592);
}