#include <vector>
#include <random>
#include "cell.h"

class Grid {

public:

    Grid(int size);

    void initializeGrid(std::mt19937& rng);

    void printGrid() const;

    void movement(int dir);

    void newNumber(std::mt19937& rng);

    int checkWin();

    int checkLose();

    ~Grid();
    
private:

    int gridSize;
    Cell** gridArray;
    
};