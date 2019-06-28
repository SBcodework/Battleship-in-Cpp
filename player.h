#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"

class Player
{
    public:
        int alive = -1;
        int pgrid[100] {0};  // Public version of grid which tracks only hits and misses on own grid
        Player();
        Player(int** _fleet[10]);
        virtual ~Player();
        int checkfleet();
        int fire(int index);
        void display();
        void foeDisplay();
        void dualdisp(Player& pfoe);

    protected:
        int grid[100] {0};
        int** fleet[10];

};

#endif // PLAYER_H
