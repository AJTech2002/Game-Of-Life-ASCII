#include "include/renderer.h"
#include <iostream>
#include <sys/_types/_int64_t.h>
#include <utility>
using namespace std;

void Renderer::clearScreen() {
  std::cout << "\033[2J\033[1;1H"; // Clear screen & move cursor to top-left
}

void Renderer::render(int x, int y, int width, int height,
                      const Grid *grid) { // Clear the console

  clearScreen();

  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      int64_t _x = x + i;
      int64_t _y = y + j;

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
