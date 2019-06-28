#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include "Player.h"

int** shipgen(int* grid, int length);
void disp(int grid[100]);
void gridplace(int** ship, int len);
int botcontroller(); // Simple for now


#endif // COMMON_H_INCLUDED
