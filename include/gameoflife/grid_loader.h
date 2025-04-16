#pragma once

#include "grid.h"

namespace GameOfLife {

/**
 * Class for loading grid data from various sources
 */
class GridLoader {
public:
    /**
     * Load grid data from standard input
     * 
     * @param grid Pointer to the grid to populate
     * @param debug Whether to print debug information
     */
    void loadStdin(Grid* grid);
    
    /**
     * Load random cells into the grid
     * 
     * @param grid Pointer to the grid to populate
     * @param numRandomCells Number of random cells to create
     * @param xStart X coordinate start range
     * @param yStart Y coordinate start range
     * @param gridWidth X coordinate end range (width)
     * @param gridHeight Y coordinate end range (height)
     */
    void loadRandom(Grid* grid, int numRandomCells, int xStart, int yStart, int gridWidth, int gridHeight);
};

} // namespace GameOfLife
