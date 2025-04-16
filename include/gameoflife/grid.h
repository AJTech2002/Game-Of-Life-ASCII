#pragma once

#include <cstdint>
#include <cstddef>
#include <utility>
#include <unordered_map>

namespace GameOfLife {

/**
 * Hash function for std::pair<int64_t, int64_t> to use in unordered_map
 */
struct pair_hash {
    std::size_t operator()(const std::pair<int64_t, int64_t>& p) const {
        std::size_t seed = 0;
        seed ^= std::hash<int64_t>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int64_t>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

/**
 * Equality function for std::pair<int64_t, int64_t> to use in unordered_map
 */
struct pair_equal {
    bool operator()(const std::pair<int64_t, int64_t>& p1, const std::pair<int64_t, int64_t>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

/**
 * Grid data structure representing the game board
 * A sparse representation using an unordered_map
 * Keys are (x,y) coordinates, values are cell states (true = alive)
 */
using Grid = std::unordered_map<std::pair<int64_t, int64_t>, bool, pair_hash, pair_equal>;

/**
 * Cell state for internal simulation use
 */
struct CellState {
    uint8_t neighborCount;
    bool isAlive;
};

/**
 * Game state maintaining double-buffered grids for simulation
 */
class GameState {
private:
    Grid bufferA;
    Grid bufferB;
    int gameIteration;
    
public:
    /**
     * Constructor initializes game iteration to 0
     */
    GameState() : gameIteration(0) {}
    
    /**
     * Get the current active grid buffer
     * @return Pointer to the current grid
     */
    Grid* currentBuffer() {
        return gameIteration % 2 == 0 ? &bufferA : &bufferB;
    }

    /**
     * Get the next grid buffer for writing
     * @return Pointer to the next grid
     */
    Grid* nextBuffer() {
        return gameIteration % 2 == 0 ? &bufferB : &bufferA;
    }

    /**
     * Increment the game iteration counter
     */
    void incrementIteration() {
        gameIteration++;
    }

    /**
     * Get the current iteration number
     * @return The current iteration
     */
    int currentIteration() const {
        return gameIteration;
    }
};

} // namespace GameOfLife