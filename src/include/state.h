#pragma once
#include <cstddef>
#include <utility>
#include <unordered_map>

// Hash the pair of int_64_t values into a single size_t value
struct pair_hash {
    std::size_t operator()(const std::pair<int64_t, int64_t>& p) const {
        std::size_t seed = 0;
        seed ^= std::hash<int64_t>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int64_t>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct pair_equal {
    bool operator()(const std::pair<int64_t, int64_t>& p1, const std::pair<int64_t, int64_t>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

using Grid = std::unordered_map<std::pair<int64_t, int64_t>, bool, pair_hash, pair_equal>;

// Hash the pair of int_64_t values into a single size_t value
struct GameState {
  private:
    Grid bufferA;
    Grid bufferB;
    int gameIteration;
    
  public:
    Grid* currentBuffer() {
        return gameIteration % 2 == 0 ? &bufferA : &bufferB;
    }

    Grid* nextBuffer() {
        return gameIteration % 2 == 0 ? &bufferB : &bufferA;
    }

    void incrementIteration() {
        gameIteration++;
    }

    int currentIteration() const {
        return gameIteration;
    }
};


