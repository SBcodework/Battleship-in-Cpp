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

void disp(int grid[100])
{
    std::cout << "\n";
    int* ptr = grid;
    for (int i=0; i<100; i++, ptr++)
    {
        if ( i % 10 == 0 ) { std::cout << "\n"; }
        std::cout << *ptr;
    }
    std::cout << "\n";
}

int** shipgen(int* grid, int length) // Grid is not supposed to change.
{
    for(;;) // Repeat process until valid ship

    {
        int start = (rand() % 100);
        if ( grid[start] == 3 ) { continue; }
        int directions[4] {1, -1, 10, -10}; // RIGHT, LEFT, DOWN, UP : used to verify directions. 0 means invalid
        int nvalid = 4;
        for (int d = 0, offset, index, xdigit = start / 10, l; d < 4; d++) // Go through directions, checking each
        {
            offset = directions[d];
            for (l = 0; l<length; l++) // For (length) times
            {
                index = start + (l * offset);
                if ( ( (d < 2) && (index / 10 != xdigit) ) || ((index<0)||(index>99))
                    || (grid[index] == 3) ) // Check if out of range, then if filled
                {
                    directions[d] = 0;
                    nvalid--;
                    break;
                }
            }
        }
        if (nvalid == 0) {continue;}
        // By this point, function will return within this iteration of the for loop
        int chosendir;
        if (nvalid == 1) {chosendir = 0;}
        else { chosendir = (rand() % nvalid); }
        // Find the index of the chosendir
        int dirIndex;
        for (int a = 0; a < 4; a++)
        {
            if ( directions[a] == 0 ) { continue; }
            if ( chosendir == 0 ) { dirIndex = a; break; }
            chosendir--;
        }
        int** ship = new int*[length];
        int offset = directions[dirIndex];
        for (int i=0, index; i<length; i++)
        {
            index = start + (i * offset);
            ship[i] = &(grid[index]);
        }
        return ship;
        break;
    }
}

void gridplace(int** ship, int len)
{
    for(int i = 0; i < len; i++)
    {
        *(ship[i]) = 3;
    }
    return;
}

int botcontroller()
{
    static int foegrid[100];
    for(;;)
    {
        int cords = rand() % 100;
        if (foegrid[cords] == 1) { continue; }
        foegrid[cords] = 1;
        return cords;
        break;
    }
}


