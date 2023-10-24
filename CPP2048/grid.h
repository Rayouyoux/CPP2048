#include "cell.h"

class Grid {

public:

    Grid(int size);

    void initializeGrid();

    void printGrid() const;

    ~Grid();

private:

    int gridSize;
    Cell** gridArray;
    
};