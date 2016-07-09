//
//  History.h
//  clang I guess
//
//  Created by Jason on 6/25/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//
#include "globals.h"


#ifndef __clang_I_guess__History__
#define __clang_I_guess__History__


class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int h_r, prevR;
    int h_c, prevC;
    char history[MAXROWS][MAXCOLS];
   void plotDot(int r, int c);
};
#endif /* defined(__clang_I_guess__History__) */
