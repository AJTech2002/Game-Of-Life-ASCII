#pragma once

#include "grid.h"

namespace GameOfLife {

/**
 * Advance the simulation one generation according to Conway's Game of Life rules
 * 
 * @param gameState Reference to the game state containing the grid buffers
 */
void step(GameState& gameState) noexcept;

} 
