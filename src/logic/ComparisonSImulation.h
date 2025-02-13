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
        auto startSequential = std::chrono::high_resolution_clock::now();
        sequentialSim.update();
        auto endSequential = std::chrono::high_resolution_clock::now();

        auto startParallel = std::chrono::high_resolution_clock::now();
        parallelSim.update();
        auto endParallel = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sequentialTime = endSequential - startSequential;
        std::chrono::duration<double> parallelTime = endParallel - startParallel;

        std::cout << "Sequential Simulation Time: " << sequentialTime.count() << " seconds" << std::endl;
        std::cout << "Parallel Simulation Time: " << parallelTime.count() << " seconds" << std::endl;
    }

private:
    SequentialSimulation sequentialSim;
    ParallelSimulation parallelSim;
};

#endif // COMPARISONSIMULATION_H
