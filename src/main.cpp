#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <sys/_types/_int64_t.h>
#include <thread>
#include <vector>
#include <cstdlib>
#include "include/renderer.h"
// get time
#include <ctime>

using namespace std;
Renderer* renderer = new Renderer();
GameState gameState = {
 .gameIteration = 0,
};

void initialise() {
 int numRandomCells = 500; 
 /*int gridWidth = INT64_MAX;*/
 /*int gridHeight = INT64_MAX;*/

  int gridWidth = 50; // Set a reasonable width for the gridHeight
  int gridHeight = 50; // Set a reasonable height for the gridHeight

  // Seed the random number generator
  std::srand(static_cast<unsigned int>(std::time(0)));

  for (int i = 0; i < numRandomCells; ++i) {
    int64_t x = rand() % gridWidth;
    int64_t y = rand() % gridHeight;
    gameState.bufferA[std::make_pair(x, y)] = true; // Mark the cell as occupied
  }
}



void step() {

  Grid* currentBuffer = gameState.gameIteration % 2 == 0 ? &gameState.bufferA : &gameState.bufferB; 
  Grid* nextBuffer = gameState.gameIteration % 2 == 0 ? &gameState.bufferB : &gameState.bufferA;

  // Clear the next buffer
  nextBuffer->clear();

  std::unordered_map<std::pair<int64_t, int64_t>, int, pair_hash> tempBuf;

  // First pass: Accumulate neighbor counts for each live cell.
  for (auto& cell : *currentBuffer) {
    int64_t x = cell.first.first;
    int64_t y = cell.first.second;
    
    // Instead of initializing the count for the cell itself,
    // just update its 8 neighbors.
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) continue; // Skip the cell itself

        if (x + dx < -INT64_MAX || x + dx > INT64_MAX ||
            y + dy < -INT64_MAX || y + dy > INT64_MAX) {
          continue; // Skip out-of-bounds cells
        }

        tempBuf[{x+dx, y+dy}] += 1;
      }
    }
  }

  // Second pass: Apply the Game of Life rules.
  for (auto& cell : tempBuf) {
    int64_t x = cell.first.first;
    int64_t y = cell.first.second;
    int count = cell.second;
    bool isAliveCurrent = (currentBuffer->find(std::make_pair(x, y)) != currentBuffer->end());
    if (isAliveCurrent) {
      // A live cell survives if it has 2 or 3 neighbors.
      if (count == 2 || count == 3) {
        (*nextBuffer)[{x, y}] = true;
      }
    }
    else {
      // A dead cell becomes alive if it has exactly 3 neighbors.
      if (count == 3) {
        (*nextBuffer)[{x, y}] = true;
      }
    }
  }

  gameState.gameIteration++;
}

int update() {
 
  step();
  std::cout << std::endl << "Game Iteration " << gameState.gameIteration <<  std::endl;

  return 0;
}

int main() {

  initialise();

  while (true) {
    renderer->clearScreen(); 
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    renderer->render(0, 0, 50, 50, gameState.gameIteration % 2 == 0 ? &gameState.bufferA : &gameState.bufferB);
    update();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}
