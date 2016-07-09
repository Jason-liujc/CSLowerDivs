#ifndef TANK_INCLUDED
#define TANK_INCLUDED
#include "Piece.h"
class Screen;
class Game;

const int MAXWIDTH=16;
const int MAXHEIGHT=21;

class Tank
{
  public:
    Tank(int width,int height);
    void display(Screen& screen, int x, int y);
    int getWidth();
    int getHeight();
    void input1(int x, int y, char a);  //to input a char value into the m_tank from out side of tank class. 
  
    void removeRow();
    char access(int x, int y);
    
private:
    char m_tank[MAXWIDTH][MAXHEIGHT]; //to store variable
    int m_width;
    int m_height;
    

};

#endif // TANK_INCLUDED
