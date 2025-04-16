#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include "gameoflife/grid.h"
#include "gameoflife/renderer.h"
#include "gameoflife/grid_loader.h"
#include "gameoflife/simulation.h"

// Structure to hold command-line options
struct ProgramOptions {
  bool debugMode;
  int iterations;
};

// Function to parse command-line arguments
ProgramOptions parseArguments(int argc, char* argv[]) {
  ProgramOptions options = {
    .debugMode = false,
    .iterations = 10,
  };

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      options.debugMode = true;
    } else if (strcmp(argv[i], "-i") == 0) {
      if (i + 1 < argc) {
        try {
          options.iterations = std::stoi(argv[i + 1]);
        } catch (const std::exception& e) {
          std::cerr << "Error: Invalid number format for iterations" << std::endl;
          options.iterations = 10; // Default value
        }
        i++; // Skip the next argument (the number)
      } 
    }
  }

  return options;
}

int main(int argc, char* argv[]) {
  using namespace GameOfLife;

  // Parse command line arguments
  ProgramOptions options = parseArguments(argc, argv);

  // Initialize components
  GridLoader gridLoader;
  Renderer renderer;
  GameState gameState;

  // Load initial grid

  gridLoader.loadStdin(gameState.currentBuffer());

  // Only sleep in debug mode
  if (options.debugMode) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  // Run simulation for specified number of iterations
  for (int i = 0; i < options.iterations; i++) {
    // Only render in debug mode
    if (options.debugMode) {
      renderer.clearScreen();
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      renderer.render(0, 0, 50, 50, gameState.currentBuffer());
    }

    // Update simulation
    step(gameState);

    // Only show iteration info and sleep in debug mode
    if (options.debugMode) { // Don't sleep after the last iteration
      std::cout << "Game Iteration " << gameState.currentIteration() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
  }

  if (options.debugMode) {
    std::cout << "\nFinal grid state:" << std::endl;
    renderer.render(0, 0, 50, 50, gameState.currentBuffer());
  } else {
    // In non-debug mode, output the final state in a format suitable for piping
    std::cout << "# Life 1.6 Output" << std::endl;
    for (const auto& cell : *gameState.currentBuffer()) {
      std::cout << cell.first.first << " " << cell.first.second << std::endl;
    }
  }

  return 0;
}
