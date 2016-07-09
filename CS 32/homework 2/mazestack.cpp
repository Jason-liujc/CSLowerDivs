//
//                                                                     I see you
//  Homework                                                       looking at this
//
//  Created by Jason on 7/13/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//


//    Push the starting coordinate (er,ec) onto the coordinate stack and
//    update maze[er][ec] to indicate that the algorithm has encountered
//    it (i.e., set maze[er][ec] to have a value other than '.').  There are also other characters you should not use.
//    While the stack is not empty,
//    {   Pop the top coordinate off the stack. This gives you the current
//        (r,c) location that your algorithm is exploring.
//        If the current (r,c) coordinate holds the Minotaur, return true!
//        Check each place you can move from the current cell:
//        If you can move NORTH and haven't encountered that cell yet,
//        then push the coordinate (r-1,c) onto the stack and update
//        maze[r-1][c] to indicate the algorithm has encountered it.
//        If you can move EAST and haven't encountered that cell yet,
//        then push the coordinate (r,c+1) onto the stack and update
//        maze[r][c+1] to indicate the algorithm has encountered it.
//        If you can move SOUTH and haven't encountered that cell yet,
//        then push the coordinate (r+1,c) onto the stack and update
//        maze[r+1][c] to indicate the algorithm has encountered it.
//        If you can move WEST and haven't encountered that cell yet,
//        then push the coordinate (r,c-1) onto the stack and update
//        maze[r][c-1] to indicate the algorithm has encountered it.
//    }
//    There was no solution, so return false
//


#include <stack>
#include <iostream>

using namespace std;
bool findsMinotaur(char maze[][10], int er, int ec);


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool findsMinotaur(char maze[][10], int er, int ec)
{
    stack<Coord> coordStack;
    Coord a(er,ec);   //the starting Coord.
    coordStack.push(a);

    maze[er][ec]='*'; // set the char
   
    while (!coordStack.empty())
    {
        Coord Lebron = coordStack.top();
        coordStack.pop();
        int temp1=Lebron.r();
        int temp2=Lebron.c();
        
        
        //if it fits M, then return true.
        if(maze[temp1][temp2]=='M')
        {
            return true;
        }
        
        
        //check each direction too see which one we can go and
        if(maze[temp1-1][temp2] != 'X'  && maze[temp1- 1][temp2] != '*')
        {
            coordStack.push(Coord(temp1 - 1, temp2));
            if(maze[temp1-1][temp2]!='M')  // check in case we overwrite M, because that's not something we want. 
            {
            maze[temp1- 1][temp2] = '*';
            }
        }
        if(maze[temp1][temp2 + 1] != 'X' && maze[temp1][temp2 + 1] != '*')
        {
            coordStack.push(Coord(temp1, temp2+ 1));
            
            if(maze[temp1][temp2+1]!='M')
            {
            maze[temp1][temp2 + 1] = '*';
            }
        }
        if(maze[temp1+ 1][temp2] != 'X'  && maze[temp1 + 1][temp2] != '*')
        {
            coordStack.push(Coord(temp1 + 1, temp2));
            
            if(maze[temp1+1][temp2]!='M')
            {
            maze[temp1 + 1][temp2] = '*';
            }
        }
        if(maze[temp1][temp2- 1] != 'X' && maze[temp1][temp2 - 1] != '*')
        {
            coordStack.push(Coord(temp1, temp2 - 1));
            
            if(maze[temp1][temp2-1]!='M')
            {
            maze[temp1][temp2 - 1] = '*';
            }
        }
    }

    
    
    
    return false;
}
#include <cassert>

void testone(int n)
{
	char maze1[10][10] = {
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'M', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
        { 'X', '.', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
        { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
        { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
        { 'X', 'X', 'X', '.', '.', 'X', '.', 'X', '.', 'X' },
        { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
        { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
        { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};
	
	char maze2[10][10] = {
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'M', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
        { 'X', 'X', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
        { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
        { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
        { 'X', 'X', 'X', '.', '.', 'X', '.', 'X', '.', 'X' },
        { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
        { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
        { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};
	
	char maze3[10][10] = {
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
        { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
        { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
        { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
        { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
        { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
        { 'X', 'M', '.', '.', '.', '.', '.', '.', 'X', 'X' },
        { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};
	
	char maze4[10][10] = {
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
        { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
        { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
        { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
        { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
        { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
        { 'X', 'M', 'X', '.', '.', '.', '.', '.', 'X', 'X' },
        { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};
    
	switch (n)
	{
	    default:
            assert(false);
	    case 1:
            assert(findsMinotaur(maze1, 8, 6));
            break;
	    case 2:
            assert(!findsMinotaur(maze2, 8, 6));
            break;
	    case 3:
            assert(findsMinotaur(maze3, 4, 3));
            break;
	    case 4:
            assert(!findsMinotaur(maze4, 4, 3));
            break;
	}
}

int main()
{
    testone(4);
}