#include <cstddef>
#include <utility>
#include <unordered_map>

// Hash the pair of int_64_t values into a single size_t value
struct pair_hash {
    std::size_t operator()(const std::pair<int64_t, int64_t>& p) const {
        return std::hash<int64_t>()(p.first) ^ (std::hash<int64_t>()(p.second) << 1);
    }

    // Check equality of two pair
    bool operator()(const std::pair<int64_t, int64_t>& p1, const std::pair<int64_t, int64_t>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

using Grid = std::unordered_map<std::pair<int64_t, int64_t>, bool, pair_hash>;

// Hash the pair of int_64_t values into a single size_t value
struct GameState {
    Grid bufferA;
    Grid bufferB;
    int gameIteration;
};


