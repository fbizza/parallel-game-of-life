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
        parallelSim.setNumThreads(numThreads);
        for (int i = 0; i < iterations; i++) {
            parallelSim.update();
        }
        parallelSim.stop();
        auto endParallel = std::chrono::high_resolution_clock::now();

        sequentialTime = std::chrono::duration<double>(endSequential - startSequential).count();
        parallelTime = std::chrono::duration<double>(endParallel - startParallel).count();
    }

    double getSequentialTime() const { return sequentialTime; }
    double getParallelTime() const { return parallelTime; }
    double getSpeedup() const { return sequentialTime / parallelTime; }

private:
    SequentialSimulation sequentialSim;
    ParallelSimulation parallelSim;
    int numThreads;
    double sequentialTime = 0.0;
    double parallelTime = 0.0;
};

#endif // COMPARISONSIMULATION_H
