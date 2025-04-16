#!/bin/bash

# Test script for Game of Life

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
INPUT_FILE="$SCRIPT_DIR/inputs/edge.txt"
EXPECTED_OUTPUT="$SCRIPT_DIR/inputs/edge-output.txt"
BINARY_PATH="$PROJECT_DIR/game_of_life"
TEMP_OUTPUT="/tmp/gameoflife_test_output.txt"

echo -e "${YELLOW}Game of Life Test Script${NC}"
echo "---------------------"
echo "Running Game of Life with Edge inputs..."
echo "Input file: $INPUT_FILE"
echo "Expected output: $EXPECTED_OUTPUT"

# Run the program with 10 iterations (default) and capture the output
$BINARY_PATH -i 10 < "$INPUT_FILE" > "$TEMP_OUTPUT"

# Check if the run was successful
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Game of Life execution failed${NC}"
    exit 1
fi

echo "Checking output against expected result..."

diff "$TEMP_OUTPUT" "$EXPECTED_OUTPUT" > /dev/null
DIFF_RESULT=$?

if [ $DIFF_RESULT -eq 0 ]; then
    echo -e "${GREEN}Test PASSED: Output matches expected result${NC}"
    # Cleanup
    rm -f "$TEMP_OUTPUT"
    exit 0
else
    echo -e "${RED}Test FAILED: Output does not match expected result${NC}"
    echo "Differences found:"
    diff "$TEMP_OUTPUT" "$EXPECTED_OUTPUT"
    
    # Keep the output for inspection
    echo "Output saved to $TEMP_OUTPUT for inspection"
    exit 1
fi
