#ifndef COMPARISONSIMULATION_H
#define COMPARISONSIMULATION_H

#include "SequentialSimulation.h"
#include "ParallelSimulation.h"
#include <chrono>
#include <iostream>

class ComparisonSimulation {
public:
    ComparisonSimulation(int width, int height, int cellSize, int numThreads = omp_get_max_threads())
        : sequentialSim(width, height, cellSize), parallelSim(width, height, cellSize), numThreads(numThreads) {}

    void runComparison() {
        const int iterations = 50;

        auto startSequential = std::chrono::high_resolution_clock::now();
        sequentialSim.start();
        for (int i = 0; i < iterations; i++) {
            sequentialSim.update();
        }
        sequentialSim.stop();
        auto endSequential = std::chrono::high_resolution_clock::now();

        auto startParallel = std::chrono::high_resolution_clock::now();
        parallelSim.start();
        for (int i = 0; i < iterations; i++) {
            parallelSim.update();
        }
        parallelSim.stop();
        auto endParallel = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sequentialTime = endSequential - startSequential;
        std::chrono::duration<double> parallelTime = endParallel - startParallel;

        std::cout << "Sequential Simulation Time for " << iterations << " iterations: "
                  << sequentialTime.count() << " seconds" << std::endl;
        std::cout << "Parallel Simulation Time for " << iterations << " iterations: "
                  << parallelTime.count() << " seconds" << std::endl;
    }

private:
    SequentialSimulation sequentialSim;
    ParallelSimulation parallelSim;
    int numThreads;
};

#endif // COMPARISONSIMULATION_H