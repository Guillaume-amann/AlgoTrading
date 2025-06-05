#include <iostream>
#include <chrono>

int main() {
    const long range = 1e10; // Sum numbers from 0 to 1e8
    long sum = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < range; ++i) {
        sum += i;
    }
    auto endTime = std::chrono::high_resolution_clock::now();

    double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
    std::cout << "Single-threaded sum: " << sum << "\n";
    std::cout << "Elapsed time: " << elapsedTime << " seconds\n";

    return 0;
}