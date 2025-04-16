#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include "gameoflife/grid_loader.h"

namespace GameOfLife {

  // Support loading from Life 1.06 format
  void GridLoader::loadStdin(Grid* grid) {
    std::string line;
    int x, y;

    while (std::getline(std::cin, line)) {
      // Skip empty lines
      if (line.empty()) {
        continue;
      }

      // Remove any comments (everything after and including '#')
      size_t commentPos = line.find('#');
      if (commentPos != std::string::npos) {
        line = line.substr(0, commentPos);
      }

      // Skip lines that become empty after comment removal
      if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
        continue;
      }

      // Parse the coordinates
      std::istringstream iss(line);
      if (!(iss >> x >> y)) {
        std::cerr << "Error reading coordinates from line: " << line << std::endl;
        continue; // Skip this line rather than breaking the whole input
      }

      // Mark the cell as occupied
      (*grid)[std::make_pair(x, y)] = true;
    }
  }

  void GridLoader::loadRandom(Grid *grid, int numRandomCells, int xStart, int yStart, int xEnd, int yEnd) {
    std::srand(std::time(0)); // Seed for random number generation

    for (int i = 0; i < numRandomCells; ++i) {
      int x = xStart + std::rand() % (xEnd - xStart + 1);
      int y = yStart + std::rand() % (yEnd - yStart + 1);

      (*grid)[std::make_pair(x, y)] = true; // Mark the cell as occupied
    }
  }

} // namespace GameOfLife
