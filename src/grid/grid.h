#ifndef GRID_H
#define GRID_H

#include <vector>
using std::vector;

class Grid {
public:
    Grid(int width, int height, int cellSize, float aliveProbability = 0.15)
        : rows(height / cellSize), columns(width / cellSize), cellSize(cellSize), cells(rows, vector<bool>(columns, 0)),
          aliveProbability(aliveProbability) {};

    void draw();

    void setValue(int row, int column, int value);

    int getValue(int row, int column);

    bool isInsideGrid(int row, int column);

    int getRows() { return rows; }
    int getColumns() { return columns; }

    void fillRandom();

    void clear();

    void toggleCell(int row, int column);

private:
    int rows;
    int columns;
    int cellSize;
    vector<vector<bool> > cells;
    float aliveProbability;
};

#endif //GRID_H
