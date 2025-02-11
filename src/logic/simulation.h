#ifndef SIMULATION_H
#define SIMULATION_H

#include "../grid/grid.h"
using std::pair;
using std::vector;

class Simulation
{
public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), tempGrid(width, height, cellSize), running(false) {}

    virtual ~Simulation() = default; // Virtual destructor for polymorphism

    void draw() { grid.draw(); }
    void setCellValue(int row, int column, int value) { grid.setValue(row, column, value); }
    int countAliveNeighbors(int row, int column) {
        int nAliveNeighbors = 0;
        vector<pair<int, int>> neighborOffsets =
        {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1},
            {-1, -1},
            {-1, 1},
            {1, -1},
            {1, 1}
        };

        for(const auto& offset : neighborOffsets)
        {
            int neighborRow = (row + offset.first + grid.getRows()) % grid.getRows();
            int neighborColumn = (column + offset.second + grid.getColumns()) % grid.getColumns();
            nAliveNeighbors += grid.getValue(neighborRow, neighborColumn);
        }
        return nAliveNeighbors;
    };
    virtual void update() = 0;  // Pure virtual function for update

    bool isRunning() const { return running; }
    void start() { running = true; }
    void stop() { running = false; }
    void clearGrid() { if (!isRunning()) grid.clear(); }
    void createRandomState() { if (!isRunning()) grid.fillRandom(); }
    void toggleCell(int row, int column) { if (!isRunning()) grid.toggleCell(row, column); }

protected:
    Grid grid;
    Grid tempGrid;
    bool running;
};

#endif //SIMULATION_H
