#include <raylib.h>
#include "grid.h"

void Grid::draw()
{
    for(int row = 0; row < rows; row ++)
    {
        for(int column = 0; column < columns; column++)
        {
            Color color = cells[row][column] ? Color{153, 255, 255, 255} : Color{0, 0, 0, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

void Grid::setValue(int row, int column, int value)
{
    if(isInsideGrid(row, column))
    {
        cells[row][column] = value;
    }
}

int Grid::getValue(int row, int column)
{
    if(isInsideGrid(row, column))
    {
        return cells[row][column];
    }
    return 0;
}

bool Grid::isInsideGrid(int row, int column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns)
    {
        return true;
    }
    return false;
}

void Grid::fillRandom()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            float randomValue = GetRandomValue(0, 100) / 100.0;
            cells[row][column] = (randomValue < aliveProbability) ? 1 : 0;
        }
    }
}

void Grid::clear()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            cells[row][column] = 0;
        }
    }
}

void Grid::toggleCell(int row, int column)
{
    if(isInsideGrid(row, column))
    {
        cells[row][column] = !cells[row][column];
    }
}