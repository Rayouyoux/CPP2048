#include <iostream>
#include "grid.h"
#include "input.h"

int main() {

    Grid gameGrid(4);

    gameGrid.initializeGrid();

    gameGrid.printGrid();

    return 0;
}