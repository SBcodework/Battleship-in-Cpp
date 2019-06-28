#include <iostream>
#include <random>
#include <time.h>
#include <cstdlib>
#include "common.h"
#include "Player.h"

Player::Player()
{
    for (int len = 5, n = 1, ***copyf = fleet, i = 0; n < 5; n++, len--)
        {
            for(i=0; i<n; i++, copyf++)
            {
                *copyf = shipgen(grid, len);
                gridplace(*copyf, len);
            }
        }
        alive = 10;
        return;
}

Player::Player(int** _fleet[10])
{
    // Deep copy because of when the function that gets user input goes out of scope (and arguments with them.)
    int*** argPtr = _fleet;
    for(int len=5,n=1, ***copyf=fleet, i=0; n<5; n++, len--)
        {
            for(i=0; i<n; i++, copyf++, argPtr++)
            {
                *copyf = *argPtr; // Remember that each ship still has allocated memory
                gridplace(*copyf, len);
            }
        }
        alive = 10;
        return;
}

Player::~Player()
{
    for (int i=0; i<10; i++)
        {
            delete fleet[i];
            fleet[i] = nullptr;
        }
        return;
}

int Player::checkfleet()
{
    // 0 - Fine, 1 - Ship sunk, 2 - Game lost
    int ntwos=1, nfours=1, sunk=0, state;//, active = 0; // Hit vs destroyed
    for(int len=5, n=1, i=0, ***ptr = fleet; n<5; n++, len--) // 4 times, per type
    {
        for(i=0; i<n; i++,ptr++) // Per ship
        {
            ntwos = 1, nfours = 1;
            for(int z = 0; z<len; z++) // For each ship cell (omitted ntwos = 2 at end and start)
            {
                state = *((*ptr)[z]);
                if ( (nfours ==1 ) && ( state != 4) )
                {
                    nfours = 0;
                    //active++;
                }
                if ( (ntwos ==1 ) && (state != 2) )
                {
                    ntwos = 0;
                }
                else {sunk = 1;}
            }
            if (ntwos)
            {
                for (int z=0; z<len; z++)
                {
                    *((*ptr)[z]) = 4;
                }
                //active--;
                alive--;
            }
        }
    }
    if (sunk)
        {
            return 1; //Ship sunk. 0 means nothing new.
        }
    if (alive == 0)
        {
            std::cout << "Fleet annihilated!\n";
            disp(grid);
            alive = 0;
            return 2; //Game lost for this player
        }
    return 0;
}

int Player::fire(int index)
{   // 0 - Miss, 1 - useless miss, 2 - useless hit, 3 - hit only, 4 - useless hit, 5 - sunk ship, 6 - Game lost for this player
    int state = -1;
    int status = 0;
    if ((index >= 0) && (index<100))
    {
        state = grid[index];
        switch (state)
        {
        case 0:
            grid[index] = 1;
            pgrid[index] = 1;
            std::cout << "Miss!\n";
            break;
        case 1:
            std::cout << "Redundant Miss!\n";
            break;
        case 2:
            std::cout << "Redundant Hit!\n";
            break;
        case 3:
            grid[index] = 2;
            pgrid[index] = 2;
            std::cout << "Hit!\n";
            status = checkfleet();
            if ((status == 2) || (alive==0))
            {
                alive = 0;
                return 6; // Fleet destroyed, game over
            }
            else
            {
                if (status == 1)
                {
                    return 5; // Ship sunk
                }
            }
            break;
        case 4:
            std::cout << "Redundant Hit!\n";
            break;
        }
    }
    return state;
}

void Player::dualdisp(Player& pfoe)
{
    std::cout << "\n";
    std::cout << "+0123456789  +0123456789\n";
    for (int i=0, *uptr = this->grid, state, *fptr = pfoe.pgrid; i<10; i++)
    {
        std::cout << i;
        for (int n=0; n<23; n++)
        {
            if ((n>9)&&(n<12)) {std::cout << " "; continue;}
            if (n==12) {std::cout << i; continue;}
            if (n<10) {state = *uptr;}
            else {state = *fptr;}
            switch (state)
            {
            case 0: // Uncharted
                std::cout << "="; break;
            case 1: // Miss
                std::cout << "o"; break;
            case 2: // Hit
                std::cout << "*"; break;
            case 3: // Ship
                std::cout << "|"; break;
            case 4: // Destroyed
                std::cout << "X"; break;
            default:
                std::cout << "error: " << state;
            }
            if (n<10) {uptr++; continue;} // Remember to ++ each pointer, else pointer read overflow occurs.
            fptr++;
        }
    std::cout << "\n";
    }
return;
}

void Player::display()
{
    disp(grid);
    return;
}

void Player::foeDisplay()
{
    disp(pgrid);
    return;
}
