#include "grid.h"
#include "helpers.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

Grid::Grid(int size) : gridSize(size) {
    gridArray = new Cell * [size];
    for (int i = 0; i < size; i++) {
        gridArray[i] = new Cell[size];
    }
}

Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] gridArray[i];
    }
    delete[] gridArray;
}

void Grid::initializeGrid(std::mt19937& rng) {
    newNumber(rng);
    newNumber(rng);
}

void Grid::printGrid() const {
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            int cellValue = gridArray[row][col].getValue();
            std::cout << cellValue << "\t";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void Grid::movement(int dir) {
    int k;
    int m;
    if (dir == 0 || dir == 1) {
        for (int i = 0; i < gridSize; i++) {
            m = 0;
            for (int j = 1; j < gridSize; j++) {
                k = 1;
                if (gridArray[j][i].getValue() != 0) {
                    while (gridArray[j - k][i].getValue() == 0) {
                        gridArray[j - k][i].setValue(gridArray[j - k + 1][i].getValue());
                        gridArray[j - k + 1][i].setValue(0);
                        k += 1;
                        if (j - k < 0 || j - k >= gridSize) {
                            break;
                        }
                    }
                    if (j - k >= 0 && j - k < gridSize) {
                        if (gridArray[j - k][i].getValue() == gridArray[j - k + 1][i].getValue()) {
                            gridArray[j - k][i].setValue((gridArray[j - k][i].getValue()) * 2);
                            gridArray[j - k + 1][i].setValue(0);
                        }
                    }
                }
            }
        }
    }
    /*
    if (dir == 0 || dir == 1) { // UP && DOWN
        for (int i = 0; i < gridSize; i++) {
            m = 0;
            for (int j = 1; j < gridSize; j++) {
                k = dir == 0 ? 1 : 2 * j - (gridSize - 1);
                std::cout << "dir : " << dir << std::endl;
                std::cout << "i : " << i << std::endl;
                std::cout << "j : " << j << std::endl;
                std::cout << "j-k : " << j-k << std::endl;
                std::cout << "-----" << std::endl;
                if (gridArray[j][i].getValue() != 0) {
                    while (gridArray[j - k][i].getValue() == 0) {
                        k = dir == 0 ? k + 1 : k - 1;
                        if (j - k < 0 || j - k >= gridSize) {
                            break;
                        }
                    }
                    std::cout<< "j-k+1" << j - k + 1 << std::endl;
                    std::cout << "j-k-1" << j - k - 1 << std::endl;
                    gridArray[dir == 0 ? j - k + 1 : j - k - 1][i].setValue(gridArray[j][i].getValue());
                    gridArray[j][i].setValue(0);
                    if ((gridArray[dir == 0 ? j - 1 : gridSize - j][i].getValue() == gridArray[j][i].getValue()) && (gridArray[j][i].getValue() != 0) && (j != m)) {
                        gridArray[dir == 0 ? j - 1 : gridSize - j][i].setValue(gridArray[dir == 0 ? j - 1 : gridSize - j][i].getValue() * 2);
                        m = j + 1;
                    }
                }
            }
        }
    }
    else if (dir == 2 || dir == 3) { // LEFT && RIGHT
        for (int i = 0; i < gridSize; i++) {
            m = 0;
            for (int j = 1; j < gridSize; j++) {
                k = dir == 2 ? 1 : 2 * j - (gridSize - 1);
                if (gridArray[i][j].getValue() != 0) {
                    while (gridArray[i][j - k].getValue() == 0) {
                        k = dir == 2 ? k + 1 : k - 1;
                        if (j - k < 0 || j - k >= gridSize) {
                            break;
                        }
                    }
                    gridArray[i][j - k +1].setValue(gridArray[i][j].getValue());
                    gridArray[i][j].setValue(0);
                    if ((gridArray[i][j + 1].getValue() == gridArray[i][j].getValue()) && (gridArray[i][j].getValue() != 0) && (j != m)) {
                        gridArray[i][j + 1].setValue(gridArray[i][j + 1].getValue() * 2);
                        m = j + 1;
                    }
                }
            }
        }
    }
    */
    /*
        else if (dir == 3) { // LEFT
            for (int i = 0; i < gridSize; i++) {
                for (int j = 1; j < gridSize; j++) {
                    k = 1;
                    if (gridArray[i][j].getValue() != 0) {
                        while (gridArray[i][j - k].getValue() == 0) {
                            k += 1;
                            if (j - k < 0) {
                                break;
                            }
                        }
                        gridArray[i][j - k + 1].setValue(gridArray[i][j].getValue());
                        gridArray[i][j].setValue(0);
                    }
                }
                for (int j = 1; j < gridSize; j++) {
                    if (gridArray[i][j - 1].getValue() == gridArray[i][j].getValue() != 0) {
                        gridArray[i][j - 1].setValue(gridArray[i - 1][j].getValue() * 2);
                    }
                }
                for (int j = 1; j < gridSize; j++) {
                    k = 1;
                    if (gridArray[i][j].getValue() != 0) {
                        while (gridArray[i][j - k].getValue() == 0) {
                            k += 1;
                            if (j - k < 0) {
                                break;
                            }
                        }
                        gridArray[i][j - k + 1].setValue(gridArray[i][j].getValue());
                        gridArray[i][j].setValue(0);
                    }
                }
            }
        }
    */
}

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

int Grid::checkLose() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == gridArray[i][j-1].getValue()) {
                return 0;
            }
        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            if (gridArray[j][i].getValue() == gridArray[j - 1][i].getValue()) {
                return 0;
            }
        }
    }
    return 1;
}
