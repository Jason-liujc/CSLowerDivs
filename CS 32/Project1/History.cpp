//
//  History.cpp
//  clang I guess
//
//  Created by Jason on 6/25/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "History.h"


History::History(int nRows,int nCols)
{
    h_r=nRows;
    h_c=nCols;
    
    
    plotDot(h_r, h_c);
    
}


bool History::record(int r, int c)
{

    if (history[r][c]=='.')
    {
        
        history[r][c]='A';
        
    }
   else
   {
       if (history[r][c]!='Z')
       history[r][c]++;
   }
    
    
    
    return true;
}


 void History::display() const
{
    clearScreen();
    for (int i=1; i<=h_r; i++)
    {
        for (int k=1; k<=h_c; k++)
        {
            std::cout << history[i][k];
        
        }
        std::cout << "\n";
        
        
    }
    
    
}

void History::plotDot(int r,int c)
{
    
    for (int i=1; i<=r; i++)
    {
        for (int k=1; k<=c; k++)
        {
            history[i][k]='.';
            
            
        }
        
        
    }
  
    
    
    
}