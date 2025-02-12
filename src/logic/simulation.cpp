#include "simulation.h"

using std::pair;
using std::vector;

Simulation::Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), tempGrid(width, height, cellSize), running(false) {
}

void Simulation::draw() {
    grid.draw();
}

void Simulation::setCellValue(int row, int column, int value) {
    grid.setValue(row, column, value);
}

int Simulation::countAliveNeighbors(int row, int column) {
    int nAliveNeighbors = 0;
    const vector<pair<int, int> > neighborOffsets =
    {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // north, south, east, west
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // diagonals
    };


    for (const auto &offset: neighborOffsets) {
        int neighborRow = (row + offset.first + grid.getRows()) % grid.getRows();
        int neighborColumn = (column + offset.second + grid.getColumns()) % grid.getColumns();
        nAliveNeighbors += grid.getValue(neighborRow, neighborColumn);
    }
    return nAliveNeighbors;
}

bool Simulation::isRunning() const {
    return running;
}

void Simulation::start() {
    running = true;
}

void Simulation::stop() {
    running = false;
}

void Simulation::clearGrid() {
    grid.clear();
}

void Simulation::createRandomState() {
    grid.fillRandom();
}

void Simulation::toggleCell(int row, int column) {
    grid.toggleCell(row, column);
}
