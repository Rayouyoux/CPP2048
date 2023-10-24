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

    int row1 = distribution(gen);
    int col1 = distribution(gen);

    int row2, col2;
    do {
        row2 = distribution(gen);
        col2 = distribution(gen);
    } while (row1 == row2 && col1 == col2);

    gridArray[row1][col1].setValue(2048);
    gridArray[row2][col2].setValue(2);
}

void Grid::printGrid() const {
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            int cellValue = gridArray[row][col].getValue();
            std::cout << cellValue << "\t";
        }
        std::cout << std::endl;
    }
}

void Grid::movement(int dir) {
    int savedValue;
    if (dir == 0) { // UP
        for (int i = 0; i < 4; i++) {
            savedValue = gridArray[0][i].getValue();
            
        }
    }
    else if (dir == 1) { // RIGHT

    }
    else if (dir == 2) { // DOWN

    }
    else if (dir == 3) { // LEFT

    }
}