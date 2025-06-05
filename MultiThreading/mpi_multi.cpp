#include <mpi.h>
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

long multiThreadedSum(long start, long end, int numThreads) {
    std::vector<std::thread> threads;
    std::vector<long> results(numThreads);
    long chunk = (end - start) / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        long threadStart = start + i * chunk;
        long threadEnd = (i == numThreads - 1) ? end : threadStart + chunk;
        threads.emplace_back(computePartialSum, threadStart, threadEnd, std::ref(results[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    long total = 0;
    for (const auto& result : results) {
        total += result;
    }
    return total;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long range = 1e10;
    long chunk = range / size;
    long start = rank * chunk;
    long end = (rank == size - 1) ? range : start + chunk;

    int numThreads = std::thread::hardware_concurrency();

    auto startTime = std::chrono::high_resolution_clock::now();
    long localSum = multiThreadedSum(start, end, numThreads);
    auto endTime = std::chrono::high_resolution_clock::now();

    long totalSum = 0;
    MPI_Reduce(&localSum, &totalSum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
    std::cout << "Rank " << rank << " local sum: " << localSum 
              << ", time: " << elapsedTime << " seconds\n";

    if (rank == 0) {
        std::cout << "Total sum: " << totalSum << "\n";
    }

    MPI_Finalize();
    return 0;
}