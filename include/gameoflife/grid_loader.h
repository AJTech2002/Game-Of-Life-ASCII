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
     * @param grid Reference to the grid to populate
     */
    void loadStdin(Grid& grid);
    
    /**
     * Load random cells into the grid
     * 
     * @param grid Reference to the grid to populate
     * @param numRandomCells Number of random cells to create
     * @param xStart X coordinate start range
     * @param yStart Y coordinate start range
     * @param xEnd X coordinate end range
     * @param yEnd Y coordinate end range
     */
    void loadRandom(Grid& grid, int numRandomCells, int xStart, int yStart, int xEnd, int yEnd);
};

}
