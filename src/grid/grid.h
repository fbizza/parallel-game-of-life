#ifndef GRID_H
#define GRID_H

#include <vector>

using std::vector;

class Grid {
public:
    Grid(int width, int height, int cellSize, float aliveProbability = 0.15);

    void draw() const;

    void setValue(int row, int column, int value);

    int getValue(int row, int column) const;

    bool isInsideGrid(int row, int column) const;

    int getRows() const;

    int getColumns() const;

    void fillRandom();

    void fillDetermined();

    void clear();

    void toggleCell(int row, int column);

private:
    int rows;
    int columns;
    int cellSize;
    float aliveProbability;
    vector<vector<bool> > cells;
};

#endif // GRID_H
