#include <iostream>
using namespace std;

// Implementation Using Variadic Templates
// Forward difference methods (Euler method)
// Forward difference for the specified variable
template <typename Func, typename... Args>
double forwardDifference(Func func, double h, double var, Args... args) {
    return (func(var + h, args...) - func(var, args...)) / h;
}

// Central difference for the specified variable
template <typename Func, typename... Args>
double centralDifference(Func func, double h, double var, Args... args) {
    // Calculate central difference for the specified variable
    return (func(var + h, args...) - func(var - h, args...)) / (2 * h);
}