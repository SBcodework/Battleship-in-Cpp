#include <iostream>
#include <random>
#include <time.h>
#include <cstdlib>
#include "common.h"
#include "Player.h"
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500 // Important to arrange this above windows.h inclusion
#endif // _WIN32_WINNT
#include <windows.h> // See above
#include <wincon.h>

int main()
{
    /*
    HANDLE hInput; // Quick Edit disabling stuff
    DWORD prev_mode;
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hInput, &prev_mode);
    DWORD new_mode = prev_mode | ENABLE_MOUSE_INPUT;
    new_mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hInput, new_mode | ENABLE_EXTENDED_FLAGS);

    HWND output = GetConsoleWindow();
    POINT point;*/
    srand(time(0));
    Player User;  // Note: calling it as <Player User()> raises error
    Player Bot;
    User.dualdisp(Bot);
    for(int cont = 1, ustate, bstate ,x, y, cord; cont; )
    {
        //std::cout << "Select a valid spot...\n";
        /*for(;;)
        {
            if ((GetCursorPos(&point)))
            {
                if (ScreenToClient(output, &point))
                {
                    std::cout << point.x << "," << point.y << "\n";
                }
            }

            Sleep(500);
        }*/

        /*CONSOLE_SELECTION_INFO selection;
        for (;;)
        {
            if (GetConsoleSelectionInfo(&selection))
            {
                std::cout << selection.dwSelectionAnchor << "\n";
            }
        }*/
        std::cout << "X? ";
        std::cin >> x;
        std::cout << "Y? ";
        std::cin >> y;
        cord = x + (y*10);
        ustate = Bot.fire(cord);
        User.dualdisp(Bot);
        if (ustate == 6) { break; }
        std::cout << "The enemy awaits commands...\n";
        Sleep(3000);
        bstate = User.fire(botcontroller());
        User.dualdisp(Bot);
        if (bstate == 6) { break; }
    }
    //SetConsoleMode(hInput, prev_mode);
    return 0;
}
