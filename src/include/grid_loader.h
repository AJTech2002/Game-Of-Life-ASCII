#pragma once
#include <iostream>
#include <string>
#include "state.h"

class GridLoader {
  
  public:
    void loadStdin (Grid* grid, bool debug); 
    void loadRandom (Grid* grid, int numRandomCells, int xStart, int yStart, int gridWidth, int gridHeight);

};
