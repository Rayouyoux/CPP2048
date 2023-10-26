#include <iostream>
#include <random>
#include <Windows.h>
#include "grid.h"
#include "input.h"
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main() {

    std::mt19937 rng(std::random_device{}());

    Grid gameGrid(4);

    gameGrid.initializeGrid(rng);

    int isRunning = 1;

    while (isRunning)
    {
        gameGrid.printGrid();

        bool badKey = true;
        while (badKey)
        {
            badKey = false;
            int c = 0;
            switch ((c = _getch()))
            {
            case KEY_UP:
                gameGrid.movement(0); // Up
                break;
            case KEY_DOWN:
                gameGrid.movement(1); // Down
                break;
            case KEY_RIGHT:
                gameGrid.movement(3); // Right
                break;
            case KEY_LEFT:
                gameGrid.movement(2); // Left
                break;
            default:
                badKey = true;
                break;
            }
        }

        gameGrid.newNumber(rng);

        if (gameGrid.checkWin() != 0) {
            std::cout << "You win!" << std::endl;
            isRunning = 0;
        }
        else if (gameGrid.checkLose() != 0) {
            std::cout << "You lose!" << std::endl;
            isRunning = 0;
        }

        system("cls");
    }


    return 0;
}