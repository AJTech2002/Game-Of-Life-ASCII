#include <limits>
#include "gameoflife/simulation.h"

namespace GameOfLife {

  static constexpr int64_t MAX_COORD = std::numeric_limits<int64_t>::max();

  // Store dx and dy offsets for the 8 neighbors (constexpr for compile-time evaluation)
  static constexpr int dx[8] = {-1, -1, -1,  0,  0,  1,  1,  1};
  static constexpr int dy[8] = {-1,  0,  1, -1,  1, -1,  0,  1};

  void step(GameState& gameState) noexcept {
    // Get buffer pointers
    const Grid* currentBuffer = gameState.currentBuffer();
    Grid* nextBuffer = gameState.nextBuffer();

    // Clear the next buffer for the new generation
    nextBuffer->clear();

    // Temporary buffer to track cell states and neighbor counts
    std::unordered_map<std::pair<int64_t, int64_t>, CellState, pair_hash, pair_equal> tempBuf;
    tempBuf.reserve(currentBuffer->size() * 2); // Reserve space for live cells and their neighbors

    // First pass: Accumulate neighbor counts for each live cell and its neighbors
    for (const auto& cell : *currentBuffer) {
      const int64_t x = cell.first.first;
      const int64_t y = cell.first.second;

      // Mark current cell as alive
      tempBuf[std::make_pair(x, y)].isAlive = true;

      // Update neighbor counts for all adjacent cells
      for (int i = 0; i < 8; ++i) {

        // Combined coordinate overflow/underflow check
        if ((dx[i] > 0 && x > MAX_COORD - dx[i]) || 
            (dx[i] < 0 && x < -MAX_COORD - dx[i]) ||
            (dy[i] > 0 && y > MAX_COORD - dy[i]) || 
            (dy[i] < 0 && y < -MAX_COORD - dy[i])) {
          continue;
        }

        const int64_t nx = x + dx[i];
        const int64_t ny = y + dy[i];

        // Increment neighbor count for the adjacent cell
        tempBuf[std::make_pair(nx, ny)].neighborCount += 1;
      }
    }

    // Second pass: Apply Conway's Game of Life rules to determine the next generation
    for (const auto& [pos, info] : tempBuf) {
      // A cell is alive in the next generation if:
      // 1. It is alive now and has 2 or 3 neighbors (survival)
      // 2. It is dead now but has exactly 3 neighbors (birth)
      if ((info.isAlive && (info.neighborCount == 2 || info.neighborCount == 3)) || 
          (!info.isAlive && info.neighborCount == 3)) {
        (*nextBuffer)[pos] = true;
      }
    }

    // Move to the next iteration
    gameState.incrementIteration();
  }
} 
