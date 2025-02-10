#ifndef SIMULATION_H
#define SIMULATION_H

#include "../grid/grid.h"

class Simulation
{
public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), tempGrid(width, height, cellSize), run(false) {};
    void draw();
    void setCellValue(int row, int column, int value);
    int countAliveNeighbors(int row, int column);
    void update();
    bool isRunning() {return run;}
    void start() {run = true;}
    void stop() {run = false;}
    void clearGrid();
    void createRandomState();
    void toggleCell(int row, int column);
private:
    Grid grid;
    Grid tempGrid;
    bool run;
};

#endif //SIMULATION_H