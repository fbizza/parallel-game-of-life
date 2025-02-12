#include "grid.h"
#include <raylib.h>

Grid::Grid(int width, int height, int cellSize, float aliveProbability)
    : rows(height / cellSize), columns(width / cellSize), cellSize(cellSize),
      aliveProbability(aliveProbability), cells(rows, vector<bool>(columns, false)) {
}

void Grid::draw() const {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            Color color = cells[row][column] ? Color{153, 255, 255, 255} : Color{0, 0, 0, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize*0.95, cellSize*0.95, color);
        }
    }
}

void Grid::setValue(int row, int column, int value) {
    if (isInsideGrid(row, column)) {
        cells[row][column] = value;
    }
}

int Grid::getValue(int row, int column) const {
    return isInsideGrid(row, column) ? cells[row][column] : 0;
}

bool Grid::isInsideGrid(int row, int column) const {
    return row >= 0 && row < rows && column >= 0 && column < columns;
}

int Grid::getRows() const {
    return rows;
}

int Grid::getColumns() const {
    return columns;
}

void Grid::fillRandom() {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            float randomValue = GetRandomValue(0, 100) / 100.0;
            cells[row][column] = (randomValue < aliveProbability);
        }
    }
}

void Grid::fillDetermined() {
    // pattern
    int pattern[8][22] = {
        {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}
    };

    // place the pattern in the center of the grid
    int startRow = (rows - 8) / 2;
    int startCol = (columns - 22) / 2;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 22; ++col) {
            setValue(startRow + row, startCol + col, pattern[row][col]);
        }
    }
}

void Grid::clear() {
    for (auto &row: cells) {
        std::fill(row.begin(), row.end(), false);
    }
}

void Grid::toggleCell(int row, int column) {
    if (isInsideGrid(row, column)) {
        cells[row][column] = !cells[row][column];
    }
}
