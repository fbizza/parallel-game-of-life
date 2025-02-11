#include "grid.h"
#include <raylib.h>


Grid::Grid(int width, int height, int cellSize, float aliveProbability)
    : rows(height / cellSize), columns(width / cellSize), cellSize(cellSize),
      aliveProbability(aliveProbability), cells(rows, std::vector<bool>(columns, false)) {}

void Grid::draw() const {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            Color color = cells[row][column] ? Color{153, 255, 255, 255} : Color{0, 0, 0, 255};

            // draw rectangles slightly smaller than cell size for having grid effect
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

void Grid::setValue(int row, int column, int value) {
    if (isInsideGrid(row, column)) {
        cells[row][column] = static_cast<bool>(value);
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
            float randomValue = static_cast<float>(GetRandomValue(0, 100)) / 100.0f;
            cells[row][column] = (randomValue < aliveProbability);
        }
    }
}

void Grid::clear() {
    for (auto& row : cells) {
        std::fill(row.begin(), row.end(), false);
    }
}

void Grid::toggleCell(int row, int column) {
    if (isInsideGrid(row, column)) {
        cells[row][column] = !cells[row][column];
    }
}
