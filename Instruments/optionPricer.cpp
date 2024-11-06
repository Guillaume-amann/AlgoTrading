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
    call.price();

    thread deltaGammaThread([&call]() {
        call.delta();
        call.gamma();
    });

    thread vegaThread([&call]() { call.vega(); });
    thread rhoThread([&call]() { call.rho(); });
    thread thetaThread([&call]() { call.theta(); });

    deltaGammaThread.join();
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

    StockOption call1(S, K, T, v, rate, 'C');
    StockOption call2(S, K, T, v, rate, 'C');

    // Measure single-threaded time
    auto startSingle = high_resolution_clock::now();
    calculateCallGreeksSingle(call1);
    auto endSingle = high_resolution_clock::now();
    auto durationSingle = duration_cast<microseconds>(endSingle - startSingle);
    cout << "Single-threaded execution time: " << durationSingle.count() << " µs" << endl;

    // Measure multi-threaded time
    auto startMulti = high_resolution_clock::now();
    calculateCallGreeksMulti(call2);
    auto endMulti = high_resolution_clock::now();
    auto durationMulti = duration_cast<microseconds>(endMulti - startMulti);
    cout << "Multi-threaded execution time: " << durationMulti.count() << " µs" << endl;

    cout << "Call option price: $" << call1.price() << endl;
    call1.displayGreeks();

    return 0;
}