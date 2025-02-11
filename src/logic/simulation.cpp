#include "simulation.h"
#include <utility>

Simulation::Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), tempGrid(width, height, cellSize), running(false) {}

Simulation::~Simulation() = default;

void Simulation::draw() {
    grid.draw();
}

void Simulation::setCellValue(int row, int column, int value) {
    grid.setValue(row, column, value);
}

int Simulation::countAliveNeighbors(int row, int column) {
    int nAliveNeighbors = 0;
    static const std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& offset : neighborOffsets) {
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
    if (!isRunning()) {
        grid.clear();
    }
}

void Simulation::createRandomState() {
    if (!isRunning()) {
        grid.fillRandom();
    }
}

void Simulation::toggleCell(int row, int column) {
    if (!isRunning()) {
        grid.toggleCell(row, column);
    }
}
