#ifndef SIMULATION_H
#define SIMULATION_H

#include "../grid/grid.h"
#include <omp.h>

class Simulation {
public:
    Simulation(int width, int height, int cellSize, int nThreads = omp_get_max_threads());

    virtual ~Simulation() = default;

    void draw();

    void setCellValue(int row, int column, int value);

    int countAliveNeighbors(int row, int column);

    virtual void update() = 0;

    bool isRunning() const;

    void start();

    void stop();

    void clearGrid();

    void createRandomState();

    void createDeterminedState();

    void createDeterminedStateScaled();

    void toggleCell(int row, int column);

    int getNumThreads() const;

    void setNumThreads(int nThreads);

protected:
    Grid grid;
    Grid tempGrid;
    bool running;
    int numThreads;
};

#endif // SIMULATION_H
