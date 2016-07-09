#include <cstdlib>
#include <algorithm>
#include "globals.h"




#ifndef UTILITIES_CPP
#define UTILITIES_CPP

// Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        std::swap(highest, lowest);
    return lowest + (std::rand() % (highest - lowest + 1));
}


#endif