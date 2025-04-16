#include <iostream>
#include <utility>
#include "gameoflife/renderer.h"

namespace GameOfLife {

  void Renderer::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen & move cursor to top-left
  }

  void Renderer::render(int x, int y, int width, int height, const Grid *grid) {
    clearScreen();

    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        int64_t _x = x + j;
        int64_t _y = y + i;

        auto it = grid->find(std::make_pair(_x, _y));
        bool occupied = false;

        if (it != grid->end()) {
          occupied = it->second; // Check if the cell is occupied
        }

        if (occupied) {
          std::cout << "X "; // Mark occupied cells with 'X'
        } else {
          std::cout << ". "; // Mark empty cells with '.'
        }
      }

      std::cout << std::endl; // Move to the next line after each row
    }
  }

} // namespace GameOfLife
