#ifndef PARALLELSIMULATION_H
#define PARALLELSIMULATION_H

#include "simulation.h"
#include <iostream>
#include <omp.h>

class ParallelSimulation : public Simulation {
public:
    ParallelSimulation(int width, int height, int cellSize)
        : Simulation(width, height, cellSize) {
    }

    void update() override {
        if (isRunning()) {
#pragma omp parallel for collapse(2)
            for (int row = 0; row < grid.getRows(); ++row) {
                for (int column = 0; column < grid.getColumns(); ++column) {
                    int liveNeighbors = countAliveNeighbors(row, column);
                    int cellValue = grid.getValue(row, column);

                    if (cellValue == 1) {
                        if (liveNeighbors > 3 || liveNeighbors < 2) {
                            tempGrid.setValue(row, column, 0);
                        } else {
                            tempGrid.setValue(row, column, 1);
                        }
                    } else {
                        if (liveNeighbors == 3) {
                            tempGrid.setValue(row, column, 1);
                        } else {
                            tempGrid.setValue(row, column, 0);
                        }
                    }
                }
            }

#pragma omp parallel for collapse(2)
            for (int row = 0; row < grid.getRows(); ++row) {
                for (int column = 0; column < grid.getColumns(); ++column) {
                    grid.setValue(row, column, tempGrid.getValue(row, column));
                }
            }
        }
    }
};

#endif //PARALLELSIMULATION_H
