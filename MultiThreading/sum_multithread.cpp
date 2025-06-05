#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void computePartialSum(long start, long end, long& result) {
    result = 0;
    for (long i = start; i < end; ++i) {
        result += i;
    }
}

int main() {
    const long range = 1e10; // Sum numbers from 0 to 1e8
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<long> results(numThreads-1);

    long chunk = range / numThreads;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        long start = i * chunk;
        long end = (i == numThreads - 1) ? range : start + chunk;
        threads.emplace_back(computePartialSum, start, end, std::ref(results[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    long totalSum = 0;
    for (const auto& result : results) {
        totalSum += result;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();

    std::cout << "Multi-threaded sum: " << totalSum << "\n";
    std::cout << "Elapsed time: " << elapsedTime << " seconds, using " << numThreads << " threads \n";

    return 0;
}