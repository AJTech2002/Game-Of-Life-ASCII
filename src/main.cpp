#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <sys/_types/_int64_t.h>
#include <sys/_types/_u_short.h>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "include/renderer.h"
#include "include/grid_loader.h"

using namespace std;

GridLoader gridLoader;
Renderer renderer;
GameState gameState;


void initialise() {
  gridLoader.loadStdin(gameState.currentBuffer(), true);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

struct CellState {
  uint8_t neighborCount;
  bool isAlive;
};

void step() {
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
    
    // Instead of initializing the count for the cell itself,
    // just update its 8 neighbors.
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) continue; // Skip the cell itself

        if (x + dx < -INT64_MAX || x + dx > INT64_MAX ||
            y + dy < -INT64_MAX || y + dy > INT64_MAX) {
          continue; // Skip out-of-bounds cells
        }

        tempBuf[{x+dx, y+dy}].neighborCount += 1;
      }
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

int update() {
 
  step();
  std::cout << std::endl << "Game Iteration " << gameState.currentIteration() <<  std::endl;

  return 0;
}

int main() {

  initialise();

  while (true) {
    renderer.clearScreen(); 
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    renderer.render(0, 0, 50, 50, gameState.currentBuffer());
    update();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}
