# Game of Life

A C++ implementation of Conway's Game of Life with support for infinite grid, command-line options, and testing.

## Features

- Infinite grid implementation using sparse data structure
- Command-line flags for debug mode and iteration control
- Input/output compatible with Life 1.6 format
- Support for rendering the grid state in the console
- Comprehensive test suite

## Building the Project

The project uses CMake as its build system. Follow these steps to build:

```bash
# Configure the project
cmake . 

# Build the project
make
```

This will create the executable `game_of_life` in the build directory.

## Running the Game

The Game of Life program reads input from standard input (stdin) in Life 1.6 format:

```bash
# Run with input from a file
./game_of_life < ../test/inputs/gliders.txt

# Or pipe input from another command
cat ../test/inputs/gliders.txt | ./game_of_life
```

### Input Format

The input format follows the Life 1.6 standard:

```
# Comments start with a # character
# Each line contains x y coordinates of a live cell
1 1
2 2
3 0
3 1
3 2
```

### Command-line Options

The program supports the following command-line options:

- `-d`: Enable debug mode (visual rendering and delays)
- `-i <num>`: Set the number of iterations (default: 10)

Examples:

```bash
# Run in debug mode with default 10 iterations
./game_of_life -d < ../test/inputs/gliders.txt

# Run 20 iterations without debug output
./game_of_life -i 20 < ../test/inputs/gliders.txt

# Run 5 iterations in debug mode
./game_of_life -d -i 5 < ../test/inputs/gliders.txt
```

### Output

- In debug mode: Visual rendering of the grid using ASCII characters
- In normal mode: Life 1.6 format output of live cell coordinates, suitable for piping to other programs

## Running Tests

After building the project, you can run the automated tests to verify that everything is working correctly:

```bash
# From the build directory
./test/test_gameoflife.sh
```

This test script:
1. Runs the Game of Life program with a predefined input (multiple gliders)
2. Compares the output to the expected result after 10 iterations
3. Reports success or failure with detailed information

## Project Structure

- `include/gameoflife/`: Public headers
- `src/`: Implementation files
- `test/`: Test files and data

## Implementation Details

- Uses double-buffering for efficient state updates
- Implements sparse grid representation for infinite universe
- Separates rendering from simulation logic

## License

[MIT License](LICENSE)
