#include <mpi.h>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long range = 1e10;
    long chunk = range / size;
    long start = rank * chunk;
    long end = (rank == size - 1) ? range : start + chunk;
    long localSum = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    for (long i = start; i < end; ++i) {
        localSum += i;
    }
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