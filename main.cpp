/**
BSD 2-Clause License

Copyright (c) 2019, SBcodework
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

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
    for(int cont = 1, ustate, bstate , x, y, cord; cont; )
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
        cord = x + (y * 10);
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
