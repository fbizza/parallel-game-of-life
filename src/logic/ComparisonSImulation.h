#ifndef COMPARISONSIMULATION_H
#define COMPARISONSIMULATION_H

#include "SequentialSimulation.h"
#include "ParallelSimulation.h"
#include <chrono>
#include <iostream>

class ComparisonSimulation {
public:
    ComparisonSimulation(int width, int height, int cellSize)
        : sequentialSim(width, height, cellSize), parallelSim(width, height, cellSize) {}

    void runComparison() {
        const int iterations = 10000000;

        auto startSequential = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            sequentialSim.update();
        }
        auto endSequential = std::chrono::high_resolution_clock::now();

        auto startParallel = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            parallelSim.update();
        }
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
};

#endif // COMPARISONSIMULATION_H