#pragma once

#include "grid.h"

namespace GameOfLife {

/**
 * Class for rendering the game grid to the console
 */
class Renderer {
public:
    /**
     * Render a portion of the grid to the console
     * 
     * @param x The starting X coordinate
     * @param y The starting Y coordinate
     * @param width The width of the area to render
     * @param height The height of the area to render
     * @param grid Pointer to the grid to render
     */
    void render(int x, int y, int width, int height, const Grid* grid);
    
    /**
     * Clear the console screen
     */
    void clearScreen();
};

} // namespace GameOfLife
