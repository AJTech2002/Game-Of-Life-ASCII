cmake_minimum_required(VERSION 3.10)
project(GameOfLife VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/grid_loader.cpp
    src/renderer.cpp
    src/simulation.cpp
)

# Main executable
add_executable(game_of_life ${SOURCES})

