#include "grid.h"
#include "helpers.h"
#include <iostream>
#include <random>

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

void Grid::initializeGrid() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(0, gridSize - 1);
    std::uniform_int_distribution<int> isFour(0, 9);

    int row1 = distribution(gen);
    int col1 = distribution(gen);
    int place4 = isFour(gen);

    int row2, col2;
    do {
        row2 = distribution(gen);
        col2 = distribution(gen);
    } while (row1 == row2 && col1 == col2);

    place4 == 9 ? gridArray[row1][col1].setValue(4) : gridArray[row1][col1].setValue(2);
    gridArray[row2][col2].setValue(2);
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
    if (dir == 0 || dir == 1) { // UP && DOWN
        for (int i = 0; i < gridSize; i++) {
            m = 0;
            for (int j = 1; j < gridSize; j++) {
                dir == 0 ? k = 1 : k = 2 * j - (gridSize - 1);
                if (gridArray[j][i].getValue() != 0) {
                    while (gridArray[j - k][i].getValue() == 0) {
                        dir == 0 ? k += 1 : k-= 1;
                        if (j - k < 0 || j - k >= gridSize) {
                            break;
                        }
                    }
                    gridArray[j - k + 1][i].setValue(gridArray[j][i].getValue());
                    gridArray[j][i].setValue(0);
                    if (gridArray[j + 1][i].getValue() == gridArray[j][i].getValue() && gridArray[j][i].getValue() != 0 && j != m) {
                        gridArray[j + 1][i].setValue(gridArray[j + 1][i].getValue() * 2);
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
                dir == 2 ? k = 1 : k = 2 * j - (gridSize - 1);
                if (gridArray[i][j].getValue() != 0) {
                    while (gridArray[i][j - k].getValue() == 0) {
                        dir == 2 ? k += 1 : k -= 1;
                        if (j - k < 0 || j - k >= gridSize) {
                            break;
                        }
                    }
                    gridArray[i][j - k +1].setValue(gridArray[i][j].getValue());
                    gridArray[i][j].setValue(0);
                    if (gridArray[i][j + 1].getValue() == gridArray[i][j].getValue() && gridArray[i][j].getValue() != 0 && j != m) {
                        gridArray[i][j + 1].setValue(gridArray[i][j + 1].getValue() * 2);
                        m = j + 1;
                    }
                }
            }
        }
    }
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

void Grid::newNumber() {


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(0, gridSize - 1);
}