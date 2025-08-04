#ifndef COMPARISONSIMULATION_H
#define COMPARISONSIMULATION_H

#include <cfloat>
#include "SequentialSimulation.h"
#include "ParallelSimulation.h"
#include <chrono>
#include <utility>

class ComparisonSimulation {
public:
    ComparisonSimulation(int width, int height, int cellSize, int numThreads = omp_get_max_threads())
        : sequentialSim(width, height, cellSize), parallelSim(width, height, cellSize), numThreads(numThreads) {
    }

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

    void generateSpeedupData(int maxThreads) {
        speedupData.clear();

        for (int threads = 1; threads <= maxThreads; ++threads) {
            std::cout << "Running benchmark with " << threads << " threads..." << std::endl;
            parallelSim.setNumThreads(threads);

            const int iterations = 50;

            auto startSeq = std::chrono::high_resolution_clock::now();
            sequentialSim.start();
            for (int i = 0; i < iterations; ++i) {
                sequentialSim.update();
            }
            sequentialSim.stop();
            auto endSeq = std::chrono::high_resolution_clock::now();

            auto startPar = std::chrono::high_resolution_clock::now();
            parallelSim.start();
            for (int i = 0; i < iterations; ++i) {
                parallelSim.update();
            }
            parallelSim.stop();
            auto endPar = std::chrono::high_resolution_clock::now();

            double seqTime = std::chrono::duration<double>(endSeq - startSeq).count();
            double parTime = std::chrono::duration<double>(endPar - startPar).count();

            double speedup = seqTime / parTime;

            speedupData.emplace_back(threads, speedup);
        }
    }

    void drawSpeedupGraph(int startX, int startY, int width, int height) {
        if (speedupData.empty()) return;

        // find max and min to scale y-axis
        float maxSpeedup = -FLT_MAX;
        float minSpeedup = FLT_MAX;
        for (const auto &[_, speedup]: speedupData) {
            if (speedup > maxSpeedup) maxSpeedup = speedup;
            if (speedup < minSpeedup) minSpeedup = speedup;
        }

        if (maxSpeedup < 1.0f) maxSpeedup = 1.0f;
        if (minSpeedup > maxSpeedup) minSpeedup = maxSpeedup;

        const int margin = 60;
        const int graphWidth = width - 2 * margin;
        const int graphHeight = height - 2 * margin;
        const int pointsCount = static_cast<int>(speedupData.size());

        // draw axes
        DrawLine(startX + margin, startY + margin, startX + margin, startY + margin + graphHeight, DARKGRAY); // Y
        DrawLine(startX + margin, startY + margin + graphHeight, startX + margin + graphWidth,
                 startY + margin + graphHeight, DARKGRAY); // X

        DrawText("Speedup", startX + 5, startY + margin - 30, 20, DARKGRAY);
        DrawText("Threads", startX + graphWidth / 2, startY + margin + graphHeight + 40, 20, DARKGRAY);

        // draw max and min labels on Y axis
        DrawText(TextFormat("%.2f", maxSpeedup), startX + 10, startY + margin - 10, 15, DARKGRAY);

        int minY = startY + margin + graphHeight - static_cast<int>((minSpeedup / maxSpeedup) * graphHeight);
        DrawText(TextFormat("%.2f", minSpeedup), startX + 10, minY - 7, 15, DARKGRAY);

        // draw points and lines
        for (int i = 0; i < pointsCount; ++i) {
            int threadCount = speedupData[i].first;
            double speedup = speedupData[i].second;

            int px = startX + margin + (graphWidth * i) / (pointsCount - 1);
            int py = startY + margin + graphHeight - static_cast<int>((speedup / maxSpeedup) * graphHeight);

            DrawCircle(px, py, 5, BLUE);

            if (i < pointsCount - 1) {
                int nx = startX + margin + (graphWidth * (i + 1)) / (pointsCount - 1);
                int ny = startY + margin + graphHeight - static_cast<int>(
                             (speedupData[i + 1].second / maxSpeedup) * graphHeight);
                DrawLine(px, py, nx, ny, SKYBLUE);
            }

            // labels for x-axis
            const char *label = TextFormat("%d", threadCount);
            int textW = MeasureText(label, 15);
            DrawText(label, px - textW / 2, startY + margin + graphHeight + 10, 15, DARKGRAY);

            // draw speedup value above each point
            const char *speedupLabel = TextFormat("%.2f", speedup);
            int speedupW = MeasureText(speedupLabel, 10);
            DrawText(speedupLabel, px - speedupW / 2, py - 20, 10, BLACK);
        }
    }


    const std::vector<std::pair<int, double> > &getSpeedupData() const {
        return speedupData;
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
    std::vector<std::pair<int, double> > speedupData;
};

#endif // COMPARISONSIMULATION_H
