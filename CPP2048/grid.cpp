#include "grid.h"
#include "helpers.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>


/*
PUBLIC METHODS
*/

void coloredValues(int value);

// Constructor
Grid::Grid(int size) : gridSize(size) {
    gridArray = new Cell * [size];
    for (int i = 0; i < size; i++) {
        gridArray[i] = new Cell[size];
    }
}

// Destructor
Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] gridArray[i];
    }
    delete[] gridArray;
}

// Initializes a game grid
void Grid::initializeGrid(std::mt19937& rng) {
    newNumber(rng);
    newNumber(rng);
}

// Prints a game grid
void coloredValues(int value) {
    // Set background color based on the value
    std::string bgColor;
    switch (value) {
    case 2:
        bgColor = "\x1b[48;5;236m";  // Light gray background
        break;
    case 4:
        bgColor = "\x1b[48;5;235m";  // Slightly darker gray background
        break;
    case 8:
        bgColor = "\x1b[48;5;208m";  // Orange background
        break;
    case 16:
        bgColor = "\x1b[48;5;202m";  // Light red background
        break;
    case 32:
        bgColor = "\x1b[48;5;196m";  // Red background
        break;
    case 64:
        bgColor = "\x1b[48;5;160m";  // Dark red background
        break;
    case 128:
        bgColor = "\x1b[48;5;226m";  // Yellow background
        break;
    case 256:
        bgColor = "\x1b[48;5;220m";  // Light orange background
        break;
    case 512:
        bgColor = "\x1b[48;5;214m";  // Orange background
        break;
    case 1024:
        bgColor = "\x1b[48;5;208m";  // Dark orange background
        break;
    case 2048:
        bgColor = "\x1b[48;5;202m";  // Light red background
        break;
    }

    std::string textColor = (value == 2 || value == 4) ? "\x1b[38;5;236m" : "\x1b[38;5;15m";

    std::cout << " | " << bgColor << value << "\t\x1b[0m";
}

void Grid::printGrid() const {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int cellValue = gridArray[i][j].getValue();
            coloredValues(cellValue);
        }
        std::cout << " | " << std::endl;
        std::cout << std::endl;
    }
}

// Choses which movement to execute based on the chosen direction
int Grid::movement(int dir) {
    return dir <= 1 ? verticalMovement(dir) : horizontalMovement(dir);
}

// Generates a new random number in a random available position in the grid
void Grid::newNumber(std::mt19937& rng) {

    std::uniform_int_distribution<int> isFour(0, 9);
    int placeFour = isFour(rng);

    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == 0) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!emptyCells.empty()) {
        std::uniform_int_distribution<std::size_t> dist(0, emptyCells.size() - 1);
        std::size_t randomIndex = dist(rng);

        std::pair<int, int> randomCoordinates = emptyCells[randomIndex];

        gridArray[randomCoordinates.first][randomCoordinates.second].setValue(placeFour == 9 ? 4 : 2);
    }
}

// Verifies if the grid containes a Cell with 2048 Value
int Grid::checkWin() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

// Checks if no movements are possible
int Grid::checkLose() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == gridArray[i][j-1].getValue()) {
                return 0;
            }
            if (gridArray[j][i].getValue() == gridArray[j - 1][i].getValue()) {
                return 0;
            }

        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) { 
            if (gridArray[i][j].getValue() == 0) {
                return 0;
            }
        }
    }
    return 1;
}


/*
PRIVATE METHODS
*/


// Vertical movement and merging
int Grid::verticalMovement(int dir) {
    int k;
    int m;
    int t;
    int isMove = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            t = dir == 0 ? j : -j + (gridSize - 1);
            k = dir == 0 ? 1 : -1;
            m = k;
            if (gridArray[t][i].getValue() != 0) {
                while (gridArray[t - k][i].getValue() == 0) {
                    gridArray[t - k][i].setValue(gridArray[t - k + m][i].getValue());
                    gridArray[t - k + m][i].setValue(0);
                    isMove = 1;
                    k = dir == 0 ? k + 1 : k - 1;
                    if (t - k < 0 || t - k >= gridSize) {
                        break;
                    }
                }
                if (t - k >= 0 && t - k < gridSize) {
                    if (gridArray[t - k][i].getValue() == gridArray[t - k + m][i].getValue()) {
                        gridArray[t - k][i].setValue((gridArray[t - k][i].getValue()) * 2);
                        gridArray[t - k + m][i].setValue(0);
                        isMove = 1;
                    }
                }
            }
        }
    }
    return isMove;
}

// Horizontal movement and merging
int Grid::horizontalMovement(int dir) {
    int k;
    int m;
    int t;
    int isMove = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            t = dir == 2 ? j : -j + (gridSize - 1);
            k = dir == 2 ? 1 : -1;
            m = k;
            if (gridArray[i][t].getValue() != 0) {
                while (gridArray[i][t - k].getValue() == 0) {
                    gridArray[i][t - k].setValue(gridArray[i][t - k + m].getValue());
                    gridArray[i][t - k + m].setValue(0);
                    isMove = 1;
                    k = dir == 2 ? k + 1 : k - 1;
                    if (t - k < 0 || t - k >= gridSize) {
                        break;
                    }
                }
                if (t - k >= 0 && t - k < gridSize) {
                    if (gridArray[i][t - k].getValue() == gridArray[i][t - k + m].getValue()) {
                        gridArray[i][t - k].setValue((gridArray[i][t - k].getValue()) * 2);
                        gridArray[i][t - k + m].setValue(0);
                        isMove = 1;
                    }
                }
            }
        }
    }
    return isMove;
}