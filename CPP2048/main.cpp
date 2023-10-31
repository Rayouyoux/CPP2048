#include <iostream>
#include <random>
#include <Windows.h>
#include "grid.h"
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
        system("cls");

        gameGrid.printGrid();

        int move = -1;
        bool badKey = true;
        while (badKey)
        {
            badKey = false;
            int c = 0;
            switch ((c = _getch()))
            {
            case KEY_UP:
                move = 0; // Up
                break;
            case KEY_DOWN:
                move = 1; // Down
                break;
            case KEY_LEFT:
                move = 2; // Left
                break;
            case KEY_RIGHT:
                move = 3; // Right
                break;
            default:
                badKey = true;
                break;
            }
        }

        int isMove = gameGrid.movement(move);
        if (isMove) {
            gameGrid.newNumber(rng);
        }

        if (gameGrid.checkWin() != 0) {
            system("cls");
            gameGrid.printGrid();
            std::cout << "You win!" << std::endl;
            isRunning = 0;
        }
        else if (gameGrid.checkLose() != 0) {
            system("cls");
            gameGrid.printGrid();
            std::cout << "You lose!" << std::endl;
            isRunning = 0;
        }
    }

    return 0;
}