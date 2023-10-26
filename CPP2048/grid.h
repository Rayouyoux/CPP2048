#include "cell.h"

class Grid {

public:

    Grid(int size);

    void initializeGrid();

    void printGrid() const;

    void movement(int dir);

    void newNumber();

    int checkWin();

    int checkLose();

    ~Grid();
    
private:

    int gridSize;
    Cell** gridArray;
    
};