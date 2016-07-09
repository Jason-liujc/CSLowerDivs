#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>


using std::string;
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    //playpiece call pick piece
    void displayPrompt(std::string s);
    void displayStatus();
    int getWidth();
    void toDollar(int posx, int posy);
    
    void getNext();
   
    void displayPiece(int orientaion, int &posx, int & posy);
    
    void clearScreen();
    
    int getHeight();
    void changePoints(int increase);
    Piece *genPiece();
    bool *getPiece();
    bool ifremove();
    void test();
    void unNext();
    void nextPiece();
    void remove();
    bool canRotate(int orientation, int posx, int posy);
    void undisplay(int posx, int posy);
    bool canMove(int direction, int posx, int posy);
    void redisplayPiece(int orientation, int &posx, int & posy);
    // [Add other members as necessary.]
    
    
    //function for special cases!
    void exeFoam(int x, int y);

  private:
    Tank    m_tank;
    Screen  m_screen;
    bool    *m_piece;
    bool    *m_next;
    int     m_level;
    int     m_width;
    int     m_height;
    int     m_points;
    string  points_string;
    int     m_rowsLeft;
    char    shape[4][4];
    int     m_time;
    bool    reachE;
    bool    endGame;
    int     m_row[5];
    int     m_rowChanged;
    
    bool    firstPiece;
    
    
    ////////boolean for the special cases!
    
    
    int     tempx;
    int     tempy;
    int     currentype;
    int     beforeType;
    
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED

