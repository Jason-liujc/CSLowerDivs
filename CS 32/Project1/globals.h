
//some global constants.

#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
class Colosseum;


int randInt(int lowest, int highest);
void clearScreen();
bool attemptMove(const Colosseum& colosseum, int dir, int& r, int& c);
bool charToDir(char ch, int& dir);


const int MAXROWS = 20;              // max number of rows in the colosseum
const int MAXCOLS = 20;              // max number of columns in the colosseum
const int MAXVILLAINS = 100;          // max number of villains allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;

#endif

