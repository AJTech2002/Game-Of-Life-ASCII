#pragma once
#include <cstdint>
#include <utility>        // for std::pair
#include <unordered_map> // for std::unordered_map
#include "state.h"


class Renderer {
public:
    void render(int x, int y, int width, int height, const Grid* grid);
    void clearScreen();
};
