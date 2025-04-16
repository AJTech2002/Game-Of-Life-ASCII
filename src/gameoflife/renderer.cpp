#include <iostream>
#include <utility>
#include "gameoflife/renderer.h"

namespace GameOfLife {

  void Renderer::clearScreen() const noexcept {
    std::cout << "\033[2J\033[1;1H"; // Clear screen & move cursor to top-left
  }

  void Renderer::render(int x, int y, int width, int height, const Grid& grid) {
    // Validate rendering bounds
    if (width <= 0 || height <= 0) {
      return; // Nothing to render
    }

    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        int64_t cellX = static_cast<int64_t>(x) + j;
        int64_t cellY = static_cast<int64_t>(y) + i;

        auto it = grid.find(std::make_pair(cellX, cellY));
        bool occupied = it != grid.end() && it->second;

        std::cout << (occupied ? "X " : ". ");
      }

      std::cout << std::endl; // Move to the next line after each row
    }
  }

} 
