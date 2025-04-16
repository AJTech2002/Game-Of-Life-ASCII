#include <iostream>
#include <limits>
#include "gameoflife/simulation.h"

namespace GameOfLife {

static const int64_t MAX_COORD = std::numeric_limits<int64_t>::max();

// Store dx and dy offsets for the 8 neighbors
static const int dx[8] = {-1, -1, -1,  0,  0,  1,  1,  1};
static const int dy[8] = {-1,  0,  1, -1,  1, -1,  0,  1};


void step(GameState& gameState) {
    // Clear the next buffer
    const Grid* currentBuffer = gameState.currentBuffer();
    Grid* nextBuffer = gameState.nextBuffer();

    nextBuffer->clear();

    std::unordered_map<std::pair<int64_t, int64_t>, CellState, pair_hash> tempBuf;

    // First pass: Accumulate neighbor counts for each live cell.
    for (const auto& cell : *currentBuffer) {
        int64_t x = cell.first.first;
        int64_t y = cell.first.second;

        tempBuf[{x, y}].isAlive = true;

        for (int i = 0; i < 8; ++i) {
            int64_t nx = x + dx[i];
            int64_t ny = y + dy[i];

            if (nx < -MAX_COORD || nx > MAX_COORD || 
                ny < -MAX_COORD || ny > MAX_COORD) {
                continue; // Skip out-of-bounds neighbors
            }

            tempBuf[{nx, ny}].neighborCount += 1;
        }
    }

    // Second pass: Apply the Game of Life rules.
    for (const auto& cell : tempBuf) {
        const auto& pos = cell.first;
        const auto& info = cell.second;
        
        if ((info.isAlive && (info.neighborCount == 2 || info.neighborCount == 3)) || 
            (!info.isAlive && info.neighborCount == 3)) {
            (*nextBuffer)[pos] = true;
        }
    }

    gameState.incrementIteration();
}
} // namespace GameOfLife
