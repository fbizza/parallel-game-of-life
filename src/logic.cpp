#include <vector>
#include <utility>
#include "logic.h"

using std::vector;
using std::pair;

void Simulation::draw()
{
    grid.draw();
}

void Simulation::setCellValue(int row, int column, int value)
{
    grid.setValue(row, column, value);
}

int Simulation::countAliveNeighbors(int row, int column)
{
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
}

void Simulation::update()
{
    if(isRunning())
    {
        for(int row = 0; row < grid.getRows(); row++)
        {
            for(int column = 0; column < grid.getColumns(); column++)
            {
                int liveNeighbors = countAliveNeighbors(row, column);
                int cellValue = grid.getValue(row, column);

                if(cellValue == 1)
                {
                    if(liveNeighbors > 3 || liveNeighbors < 2)
                    {
                        tempGrid.setValue(row, column, 0);
                    }
                    else
                    {
                        tempGrid.setValue(row, column, 1);
                    }
                }
                else
                {
                    if(liveNeighbors == 3)
                    {
                        tempGrid.setValue(row, column, 1);
                    }
                    else
                    {
                        tempGrid.setValue(row, column, 0);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::clearGrid()
{
    if(!isRunning())
    {
        grid.clear();
    }
}

void Simulation::createRandomState()
{
    if(!isRunning())
    {
        grid.fillRandom();
    }
}

void Simulation::toggleCell(int row, int column)
{
    if(!isRunning())
    {
        grid.toggleCell(row, column);
    }
}