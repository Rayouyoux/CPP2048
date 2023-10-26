#include <iostream>
#include <Windows.h>
#include "input.h"

using namespace std;

namespace Input
{

    int keyPressed() {
        if (GetKeyState(VK_UP) & 0x8000 || GetKeyState('z') & 0x8000)
        {
            while (GetKeyState(VK_UP) & 0x8000 || GetKeyState('z') & 0x8000) {
                //cout << "papagnattend" << endl;
            }
            cout << "up" << endl;
            return 0;
        }
        if (GetKeyState(VK_DOWN) & 0x8000 || GetKeyState('s') & 0x8000)
        {
            while (GetKeyState(VK_DOWN) & 0x8000 || GetKeyState('s') & 0x8000) {
                //cout << "papagnattend" << endl;
            }
            cout << "down" << endl;
            return 1;
        }
        if (GetKeyState(VK_LEFT) & 0x8000 || GetKeyState('q') & 0x8000)
        {
            while (GetKeyState(VK_LEFT) & 0x8000 || GetKeyState('q') & 0x8000) {
                //cout << "papagnattend" << endl;
            }
            cout << "left" << endl;
            return 2;
        }
        if (GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState('d') & 0x8000)
        {
            while (GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState('d') & 0x8000) {
                //cout << "papagnattend" << endl;
            }
            cout << "right" << endl;
            return 3;
        }
    }

    bool quit() {
        if (GetKeyState(VK_ESCAPE) & 0x8000)
        {
            cout << "quit" << endl;
            return false;
        }
    }
};