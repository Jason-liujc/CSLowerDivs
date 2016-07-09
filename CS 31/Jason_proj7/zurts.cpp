#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cassert>
using namespace std;


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXZURTS = 100;          // max number of zurts allowed
const int MAXCOLORS = 3;           // max number of colors
const double WALL_DENSITY = 0.13;  // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int WALL  = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Zurt declaration.

class Zurt
{
public:
    // Constructor
    Zurt(Arena* ap, int r, int c, char color);
    
    // Accessors
    int  row() const;
    int  col() const;
    char color() const;
    bool isDead() const;
    
    // Mutators
    void forceMove(int dir);
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    char   m_color;
    int m_health=3;
};

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string stand();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zurtCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfZurtsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void   setCellStatus(int r, int c, int status);
    bool   addZurt(int r, int c, char color);
    bool   addPlayer(int r, int c);
    string moveZurts(char color, int dir);
    
private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zurt*   m_zurts[MAXZURTS];
    int     m_nZurts;
    
    // Helper functions
    void checkPos(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZurts);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
    string takeZurtsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool charToDir(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();
void dirSuggest(int &dir);

///////////////////////////////////////////////////////////////////////////
//  Zurt implementation
///////////////////////////////////////////////////////////////////////////

Zurt::Zurt(Arena* ap, int r, int c, char color)
{
    if (ap == nullptr)
    {
        cout << "***** A zurt must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Zurt created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
    {
        cout << "***** Zurt created with invalid color " << color << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_color = color;
}

int Zurt::row() const
{
    return m_row;
}

int Zurt::col() const
{
    return m_col;
}

char Zurt::color() const
{
    return m_color;
}

bool Zurt::isDead() const //judge whether the zurt is dead or not.
{
    if (m_health<=0)
        return true;
    else
        return false;
}

void Zurt::forceMove(int dir)  //force the zurts to move in a certain direction, if it is not successful, deduct the hit point
{
    if (attemptMove(*m_arena, dir, m_row, m_col)==false)
        m_health--;
   
    
}

void Zurt::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    if (!isDead())
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::stand()
{
    return "Player stands.";
}

string Player::move(int dir)
{
    //use attemptMove, if it's false we say that the player couldn't move.
    if (attemptMove(*m_arena, dir, m_row, m_col)==false)
        {
        return "Player couldn't move; player stands.";
        }
    
    switch (dir) {
            //use numberOfZurts to figure out whether there are zurts in the column after it moves.

        case NORTH:
            if (m_arena->numberOfZurtsAt(m_row, m_col)>0)
            {
                setDead();
                return "Player walked into a zurt and died.";
            }
            break;
            
        case SOUTH:
            if (m_arena->numberOfZurtsAt(m_row, m_col)>0)
            {
                setDead();
                return "Player walked into a zurt and died.";
            }
            break;
        case WEST:
            if (m_arena->numberOfZurtsAt(m_row, m_col)>0)
            {
                setDead();
                return "Player walked into a zurt and died.";
            }
            break;
        case EAST:
            if (m_arena->numberOfZurtsAt(m_row, m_col)>0)
            {
                setDead();
                return "Player walked into a zurt and died.";
            }
            break;
        default:
            break;
            
    }
    
    //the cases when the player actually moves.
    if (dir==NORTH)
    {
        return "Player moved north.";
    }
    else if (dir==SOUTH)
    {
        return "Player moved south.";
    }
    else if (dir==WEST)
    {
        return "Player moved west.";
    }
    else                                        ////////////kinda dangerous.//////////
    {
        return "Player moved east.";
    }
    
    
    
    
    
}

bool Player::isDead() const  //if the player is dead return true.
{
    if (m_dead==false)
        return false;
    else
        return true;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nZurts = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena() //If you didn't create an object with new, you can't delete it.
{
    for (int i=0; i<m_nZurts; i++) //delete the object created by new so that the program does not leak memory.
    {
        delete []m_zurts[i];
        
        
        
        
    }
    delete []m_player;
    
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::zurtCount() const
{
    return m_nZurts;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Arena::numberOfZurtsAt(int r, int c) const // measure the number of zurts
{
    int counter=0;
    int row;
    int column;
    for (int i=0; i<m_nZurts; i++)
    {
        row=m_zurts[i]->row();
        column=m_zurts[i]->col();
       if (row==r && column==c)
           counter++;
        
        
    }
    
    return counter;
    
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');
    
    // Indicate zurt positions by their colors.  If more than one zurt
    // occupies a cell, show just one (any one will do).
    
   
    for (int i=0; i<m_nZurts; i++)
    {
        
        if (m_zurts[i]->color()=='Y'){
              displayGrid[m_zurts[i]->row()-1][m_zurts[i]->col()-1]='Y';
        }else if (m_zurts[i]->color()=='R'){
            displayGrid[m_zurts[i]->row()-1][m_zurts[i]->col()-1]='R';
        }else if (m_zurts[i]->color()=='B'){
            displayGrid[m_zurts[i]->row()-1][m_zurts[i]->col()-1]='B';
        }
    }
        
        
    
    
    
    // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, zurt, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zurtCount() << " zurts remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Arena::addZurt(int r, int c, char color)
{
    if (m_nZurts == MAXZURTS)
        return false;
    m_zurts[m_nZurts] = new Zurt(this, r, c, color);
    m_nZurts++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != nullptr)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveZurts(char color, int dir)
{
    // Zurts of the indicated color will follow that color with probability 1/2
    bool willFollow = (randInt(0, 1) == 0);
    int row2;
    int column2;
    
    
    // Move all zurts
    int nZurtsOriginally = m_nZurts;

    if(color=='Y') //if it's certain color Yellow.
    {
        for (int i=0; i<m_nZurts; i++)
        {
            if (m_zurts[i]->color()=='Y')
            {
             if (willFollow)
             {
                 row2=m_zurts[i]->row();
                 column2=m_zurts[i]->col();
                 m_zurts[i]->forceMove(dir);
                 if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                 {
                     m_player->setDead();
            
                 }
             }
                
                
                else
                {
                    m_zurts[i]->move();
                    if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                    {
                        m_player->setDead();
             
                    }
                    
                }
                
            }
            
            else
            {
                m_zurts[i]->move();
                if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                {
                    m_player->setDead();
                    
                }
                
            }
            
        }
    }
    
    if(color=='R')  //if it's certain color Red.
    {
        for (int i=0; i<m_nZurts; i++)
        {
            if (m_zurts[i]->color()=='R')
            {
                if (willFollow)
                {
                    row2=m_zurts[i]->row();
                    column2=m_zurts[i]->col();
                    m_zurts[i]->forceMove(dir);
                     if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                    {
                        m_player->setDead();
                    }
                }
                
                
                else
                {
                     m_zurts[i]->move();
                   if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                    {
                        m_player->setDead();
                       
                    }
                }
                
            }
            
            else
            {
                 m_zurts[i]->move();
                 if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                {
                    m_player->setDead();
                
                }
                
                
            }
        }
    }
    
    if(color=='B') // //if it's certain color Black.
    {
        for (int i=0; i<m_nZurts; i++)
        {
            if (m_zurts[i]->color()=='B')
            {
                if (willFollow)
                {
                    row2=m_zurts[i]->row();
                    column2=m_zurts[i]->col();
                    m_zurts[i]->forceMove(dir);
                    if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                    {
                        m_player->setDead();
                        
                    }
                }
                
                
                else
                {
                    m_zurts[i]->move();
                   if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                    {
                        m_player->setDead();
                        
                    }
                }
                
            }
            
            else
            {
              m_zurts[i]->move();
                if (numberOfZurtsAt(m_player->row(), m_player->col())>0)
                {
                    m_player->setDead();
                }
                
            }
        }
    }
    
    
    for (int i=0; i<m_nZurts; i++)
        //delete the zurt and decrease the zurt count once a zurt is dead.
    {
        if (m_zurts[i]->isDead())
        {
            
            for (int k=i; k<m_nZurts; k++)
            {
                m_zurts[k]=m_zurts[k+1];
            }
            
            
            m_nZurts--;
            
        }
        
    }
    
  
    
    if (m_nZurts < nZurtsOriginally)
        return "Some zurts have been destroyed.";
    else
        return "No zurts were destroyed.";
}

void Arena::checkPos(int r, int c) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  || c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
        << c << ")" << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZurts)
{
    if (nZurts < 0  ||  nZurts > MAXZURTS)
    {
        cout << "***** Game created with invalid number of zurts:  "
        << nZurts << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nZurts - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
        << cols << " arena, which is too small too hold a player and "
        << nZurts << " zurts!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add some walls in WALL_DENSITY of the empty spots
    assert(WALL_DENSITY >= 0  &&  WALL_DENSITY <= 1);
    int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
    while (nWalls > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->getCellStatus(r, c) == WALL)
            continue;
        m_arena->setCellStatus(r, c, WALL);
        nWalls--;
    }
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with zurts
    while (nZurts > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->getCellStatus(r,c) != EMPTY  ||  (r == rPlayer && c == cPlayer))
            continue;
        const char colors[MAXCOLORS] = { 'R', 'Y', 'B' };
        m_arena->addZurt(r, c, colors[randInt(1, MAXCOLORS)-1]);
        nZurts--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->stand();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->stand();
            else if (charToDir(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string Game::takeZurtsTurn()
{
    for (;;)
    {
        cout << "Color thrown and direction (e.g., Rn or bw): ";
        string colorAndDir;
        getline(cin, colorAndDir);
        if (colorAndDir.size() != 2)
        {
            cout << "You must specify a color followed by a direction." << endl;
            continue;
        }
        char color = toupper(colorAndDir[0]);
        if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        {
            cout << "Color must be upper or lower R, Y, or B." << endl;
            continue;
        }
        int dir;
        if (charToDir(colorAndDir[1], dir))
            return m_arena->moveZurts(color, dir);
        else
            cout << "Direction must be n, e, s, or w." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    while ( ! m_arena->player()->isDead()  &&  m_arena->zurtCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        Player* player = m_arena->player();
        if (player->isDead())
            break;
        msg = takeZurtsTurn();
        m_arena->display(msg);
    }
    if (m_arena->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations (except clearScreen)
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

bool charToDir(char ch, int& dir)
{
    switch (tolower(ch))
    {
        default:  return false;
        case 'n': dir = NORTH; break;
        case 'e': dir = EAST;  break;
        case 's': dir = SOUTH; break;
        case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would hit a wall or run off the edge of the
// arena.  Otherwise, update r and c to the position resulting from the
// move and return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    
    //moves in different directions
    if (dir==NORTH)
    {
        
        if (r-1<1)
            return false;
        if (a.getCellStatus(r-1, c) == WALL)
            return false;
        
            r--;
        
        
        
    
    }
    else if (dir==SOUTH)
    {
        
        if (r+1>a.rows())
            return false;

        if (a.getCellStatus(r+1, c) == WALL)
            return false;
        
      
            
            r++;
        
        
        
    }
    
    else if (dir==WEST)
    {
        if (c-1<1)
            return false;
        if (a.getCellStatus(r, c-1) == WALL)
            return false;
       
        
        
            c--;
        
        
        
        
    }
    
    
    else if (dir==EAST)
    {
        
        if (c+1>a.cols())
            return false;
        
        if(a.getCellStatus(r, c+1) == WALL)
            return false;
        
        
            c++;
        
    }
    
    
    else
    {
        //when it's not one of the four directions
        return false;
    }
    return true;
    
    
        
}






// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should stand; otherwise, bestDir is
// set to the recommended direction to move.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    
    int pCol=a.player()->col();
    int pRow=a.player()->row();
    
    
   
    
   //here's a list of logical conditions that the numberOfZurts have to satisfy.
   
    if (pRow>1) //the reason I do this is because to prevent the checkpos function access certain area that is out of bound.
    {
        int nTop=a.numberOfZurtsAt(pRow-1,pCol);
        
        if (pRow<a.rows())
        {
             int nBottom=a.numberOfZurtsAt(pRow+1, pCol);
            
            if (pCol>1)
            {
                int nLeft=a.numberOfZurtsAt(pRow, pCol-1);
                
                if (pCol<a.cols())
                {
                     int nRight=a.numberOfZurtsAt(pRow, pCol+1);
                    
                    
                    
                    //one of them is zero.
                    if (nLeft==0 && nRight>0 && nTop>0 && nBottom>0)
                    {
                        bestDir=WEST;
                        
                        
                    }
                    if (nLeft>0 && nRight==0 && nTop>0 && nBottom>0)
                    {
                        
                        bestDir=EAST;
                        
                    }
                    
                    
                    if (nLeft>0 && nRight>0 && nTop==0 && nBottom>0)
                    {
                        
                        bestDir=NORTH;
                        
                    }
                    
                    
                    if (nLeft>0 && nRight>0 && nTop>0 && nBottom==0)
                    {
                        
                        bestDir=SOUTH;
                        
                    }
                    
                    //two of them are zero
                    if (nLeft+nRight==0)
                    {
                        if (pCol>(a.cols()-pCol))
                        bestDir=WEST;
                        else
                            bestDir=EAST;
                        
                    }
                    
                    if(nLeft+nTop==0)
                    {
                        if (pRow>pCol)
                        bestDir=NORTH;
                        else
                            bestDir=WEST;
                    
                        
                        
                        
                    }
                    
                    if(nLeft+nBottom==0)
                    {
                        
                        if ((a.rows()-pRow)>pCol)
                            bestDir=SOUTH;
                        else
                            bestDir=WEST;
                        
                        
                        
                        
                    }
                    
                    
                    
                    if (nRight+nTop==0)
                    {
                        
                        
                        if (pRow>(a.cols()-pCol))
                            bestDir=NORTH;
                        else
                            bestDir=EAST;
                        
                        
            
                    }
                    
                    
                    
                    if(nRight+nBottom==0)
                    {
                        
                        if ((a.rows()-pRow)>(a.cols()-pCol))
                            bestDir=SOUTH;
                        else
                            bestDir=EAST;
                        
                        
                        
                        
                    }
                    
                    
                    
                    if(nTop+nBottom==0)
                    {
                        
                        
                        if (pCol>(a.cols()-pCol))
                            bestDir=NORTH;
                        else
                            bestDir=SOUTH;
                        
                        
                        
                        
                    }
                    
                    
                    
                    //non of them are zero
                    if (nLeft>0 && nRight>0 && nTop>0 && nBottom>0)  // if the player is surrounded by zurts
                    {
                        
                        return false;
                        
                    }
                    
                    //three of them are zero.
                    if (nLeft==0 && nRight==0 && nTop==0 && nBottom>0)
                    {
                        
                        bestDir=NORTH;
                        
                    }
                    
                    if (nLeft==0 && nRight==0 && nTop>0 && nBottom==0)
                    {
                        
                        bestDir=SOUTH;
                        
                    }
                    if (nLeft==0 && nRight>0 && nTop==0 && nBottom==0)
                    {
                        
                        bestDir=WEST;
                        
                    }
                    if (nLeft>0 && nRight==0 && nTop==0 && nBottom==0)
                    {
                        
                        bestDir=EAST;
                        
                    }
                    
                    //if all of them zero.
                    
                    if (nLeft==0 && nRight==0 && nTop==0 && nBottom==0)  // if the player is surrounded by zurts
                    {
                        return false;
                        
                    }
                }
                
                
                else{
               
                if (nLeft==0)
                
                    bestDir=WEST;
                
                if (nTop==0)
                    bestDir=NORTH;
                if (nBottom==0)
                    bestDir=SOUTH;
     
                }
                
            }
            else
            {
                int nRight=a.numberOfZurtsAt(pRow, pCol+1);
                if (nRight>0)
                    bestDir=EAST;
                
                if (nBottom>0)
                    bestDir=SOUTH;
                
                if (nTop>0)
                    bestDir=NORTH;
                
                
                
                
                
            }
            
  
            
        }
        
        else
            
        {
            if (pCol==a.cols())
            {
                  int nLeft=a.numberOfZurtsAt(pRow, pCol-1);

                if (nTop==0)
                     bestDir=NORTH;
                if (nLeft==0)
                    bestDir=WEST;
                
                
            }
            if (pCol==1)
            {
                 int nRight=a.numberOfZurtsAt(pRow, pCol+1);
                
                if (nTop==0)
                    bestDir=NORTH;
                
                if(nRight==0)
                    bestDir=EAST;
                
                
                
            }
            
            
        }

    }
    
    else{
        if (pCol==a.cols())
        {
            int nBottom=a.numberOfZurtsAt(pRow+1, pCol);
            int nLeft=a.numberOfZurtsAt(pRow, pCol-1);
            
            if (nBottom==0)
                bestDir=SOUTH;
            if (nLeft==0)
                bestDir=WEST;
            
            
        }
        if (pCol==1)
        {
            int nBottom=a.numberOfZurtsAt(pRow+1, pCol);
            int nRight=a.numberOfZurtsAt(pRow, pCol+1);
            
            if (nBottom ==0)
                bestDir=SOUTH;
            
            if(nRight==0)
                bestDir=EAST;
            
            
            
        }
        
        
        
    }
    
    // Your replacement implementation should do something intelligent.
    // For example, if you're standing next to four zurts, and moving
    // north would put you next to two zurts, but moving east would put
    // you next to none, moving east is a safer choice than standing or
    // moving north.
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////


int main()
{
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
 
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 10, 20);
   
    // Play the game
    g.play();
    
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif