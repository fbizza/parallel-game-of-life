#ifndef SIMULATION_H
#define SIMULATION_H

#include "../grid/grid.h"

class Simulation {
public:
    Simulation(int width, int height, int cellSize);
    virtual ~Simulation();
    void draw();
    void setCellValue(int row, int column, int value);
    int countAliveNeighbors(int row, int column);
    virtual void update() = 0;
    bool isRunning() const;
    void start();
    void stop();
    void clearGrid();
    void createRandomState();
    void toggleCell(int row, int column);

protected:
    Grid grid;
    Grid tempGrid;
    bool running;
};

#endif // SIMULATION_H
