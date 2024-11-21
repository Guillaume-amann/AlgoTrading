#pragma once
// Distributions.h is being included multiple times in the project, which causes redefinition errors.
// To prevent this, we need to ensure that the header file is only included once per compilation unit.
// You can achieve this by adding include guards or using #pragma once at the top of the header file.

#include <iostream>
using namespace std;

// Standard normal cumulative distribution function
double stdN(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

// Normal density function
double normal(double x) {
    return exp(-x * x * 0.5) / sqrt(2 * 3.141592);
}