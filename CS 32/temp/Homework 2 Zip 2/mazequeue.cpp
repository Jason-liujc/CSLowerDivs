

#include <iostream>
#include <queue>
using namespace std;

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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','.','X','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr,sc));
    maze[sr][sc] = '/';
    while (!coordQueue.empty())
    {
        Coord b = coordQueue.front();
        coordQueue.pop();
        if(b.r() == er && b.c() == ec)
        {
            return true;
        }
        if(maze[b.r() - 1][b.c()] != 'X' && maze[b.r() - 1][b.c()] != 'x' && maze[b.r() - 1][b.c()] != '/')
        {
            coordQueue.push(Coord(b.r() - 1, b.c()));
            maze[b.r() - 1][b.c()] = '/';
        }
        if(maze[b.r()][b.c() + 1] != 'X' && maze[b.r()][b.c() + 1] != 'x' && maze[b.r()][b.c() + 1] != '/')
        {
            coordQueue.push(Coord(b.r(), b.c() + 1));
            maze[b.r()][b.c() + 1] = '/';
        }
        if(maze[b.r() + 1][b.c()] != 'X' && maze[b.r() + 1][b.c()] != 'x' && maze[b.r() + 1][b.c()] != '/')
        {
            coordQueue.push(Coord(b.r() + 1, b.c()));
            maze[b.r() + 1][b.c()] = '/';
        }
        if(maze[b.r()][b.c() - 1] != 'X' && maze[b.r()][b.c() - 1] != 'x' && maze[b.r()][b.c() - 1] != '/')
        {
            coordQueue.push(Coord(b.r(), b.c() - 1));
            maze[b.r()][b.c() - 1] = '/';
        }
    }
    return false;
}
/*Push the starting coordinate (sr,sc) onto the coordinate stack and
 update maze[sr][sc] to indicate that the algorithm has encountered
 it (i.e., set maze[sr][sc] to have a value other than '.').
 While the stack is not empty,
 {   Pop the top coordinate off the stack. This gives you the current
 (r,c) location that your algorithm is exploring.
 If the current (r,c) coordinate is equal to the ending coordinate,
 then we've solved the maze so return true!
 Check each place you can move from the current cell:
 If you can move NORTH and haven't encountered that cell yet,
 then push the coordinate (r-1,c) onto the stack and update
 maze[r-1][c] to indicate the algorithm has encountered it.
 If you can move EAST and haven't encountered that cell yet,
 then push the coordinate (r,c+1) onto the stack and update
 maze[r][c+1] to indicate the algorithm has encountered it.
 If you can move SOUTH and haven't encountered that cell yet,
 then push the coordinate (r+1,c) onto the stack and update
 maze[r+1][c] to indicate the algorithm has encountered it.
 If you can move WEST and haven't encountered that cell yet,
 then push the coordinate (r,c-1) onto the stack and update
 maze[r][c-1] to indicate the algorithm has encountered it.
 }
 There was no solution, so return false */