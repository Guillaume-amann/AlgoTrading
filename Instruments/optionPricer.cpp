#include <iostream>
#include <chrono>
#include <thread>
#include "Options.h"

using namespace std;
using namespace std::chrono;

void calculateCallGreeksSingle(StockOption &call) {
    call.price();
    call.delta();
    call.gamma();
    call.vega();
    call.rho();
    call.theta();
}


// Multithreaded calculation
void calculateCallGreeksMulti(StockOption &call) {
    thread priceThread(&StockOption::price, &call);
    thread deltaThread(&StockOption::delta, &call);
    thread gammaThread(&StockOption::gamma, &call);
    thread vegaThread(&StockOption::vega, &call);
    thread rhoThread(&StockOption::rho, &call);
    thread thetaThread(&StockOption::theta, &call);

    priceThread.join();
    deltaThread.join();
    gammaThread.join();
    vegaThread.join();
    rhoThread.join();
    thetaThread.join();
}

int main() {
    double S = 100.0;  // Stock Price S
    double K = 100.0;  // Strike Price K
    double T = 1;      // Years to maturity
    double v = 0.20;   // Yearly volatility in %
    double rate = 0.0325;

    StockOption call(S, K, T, v, rate, 'C');

    // Measure single-threaded time
    auto startSingle = high_resolution_clock::now();
    calculateCallGreeksSingle(call);
    auto endSingle = high_resolution_clock::now();
    auto durationSingle = duration_cast<microseconds>(endSingle - startSingle);
    cout << "Single-threaded execution time: " << durationSingle.count() << " µs" << endl;

    // Measure multi-threaded time
    auto startMulti = high_resolution_clock::now();
    calculateCallGreeksMulti(call);
    auto endMulti = high_resolution_clock::now();
    auto durationMulti = duration_cast<microseconds>(endMulti - startMulti);
    cout << "Multi-threaded execution time: " << durationMulti.count() << " µs" << endl;

    return 0;
}