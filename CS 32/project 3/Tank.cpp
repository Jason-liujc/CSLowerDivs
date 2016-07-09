#include "Tank.h"
#include "UserInterface.h"

Tank::Tank(int width, int height)
{
    m_width=width;
    m_height=height;
    
    
    //starting from 1, create a U shaped @ lists
    for (int i=0; i<m_height+1;i++)
    {
       m_tank[0][i]='@';
    
   
        m_tank[m_width+1][i]='@';
    }
    
    for (int i=0; i<m_width+1; i++)
        m_tank[i][m_height]='@';
    
    for (int k=0 ; k<m_height; k++)
    {
        for (int i=1; i<=m_width; i++)
        {
            m_tank[i][k]=' ';
            
        }
    
    }
    
    
}
//never used, might be in the future
int Tank::getHeight()
{
    return m_height;
    
    
}

int Tank::getWidth()
{
    return m_width;
}


//display the tank using characters from m_tank

void Tank::display(Screen& screen, int x, int y)
{
    x=m_width+1;
    y=m_height;
    //print left part
    for (int i=0; i<=y; i++)
    {
        screen.gotoXY(0, i);
        screen.printChar(m_tank[0][i]);
        screen.gotoXY(x, i);
        screen.printChar(m_tank[x][i]);
    }
    
    for (int i=0; i<=x; i++)
    {
        screen.gotoXY(i, y);
        screen.printChar(m_tank[i][y]);

    }
    
    
    
    
    
}




void Tank::input1(int x, int y, char a)
{
    m_tank[x][y]=a;
    
    
}




char Tank::access(int x, int y)
{
    return m_tank[x][y];
    
}
