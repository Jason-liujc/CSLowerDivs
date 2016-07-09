#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include <string>
#include <iostream>
#include "randPieceType.h"
#include <algorithm> //for max function

using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;


const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT),  m_tank(width, height)
{
    m_points=0;
    m_width=width;
    m_height=height;
   
    m_level=1;
    m_rowsLeft=5*m_level;
    m_rowChanged=0;
    m_time=std::max(100,1000-(100*(m_level-1)));
    
   
    
    m_row[0]=0;
    m_row[1]=0;
    m_row[2]=0;
    m_row[3]=0;
    m_row[4]=0;
    currentype=0;
    beforeType=0;
    
}

void Game::play()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);

    displayStatus();  //  score, rows left, level
    
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        
        if(endGame)
            break;
        clearScreen();
        
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_rowsLeft=5*m_level;
        displayStatus();
        
    }

    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}
//piece *pickpiece

void Game::clearScreen()
{
    //clear the screen except edges.
    for (int k=0 ; k<m_height; k++)
    {
        for (int i=1; i<=m_width; i++)
        {
            
            m_tank.input1(i, k, ' ');
            m_screen.gotoXY(i,k);
            m_screen.printChar(' ');
            
        }
      
    }
    
    
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}
int Game::getWidth()
{
    return m_width;
}

int Game::getHeight()
{
    return m_height;
}
void Game::displayStatus()
{
    
    int temp=m_points/10;   //I don't know why!!!
    int digits=0;
    //number of digits
    while (temp) {
        temp /= 10;
        digits++;
    }
    
 
    m_screen.gotoXY(SCORE_X, SCORE_Y);
   
    string space;
    
    for (int i=7; i>=digits; i--)
    {
        space=space+' ';
    }
    
    m_screen.printString("Score:   "+space+std::to_string(m_points));
    
    temp=m_level;
    digits=0;
    while (temp) {
        temp /= 10;
        digits++;
    }
    string space2;
    for (int i=7; i>=digits; i--)
    {
        space2=space2+' ';
    }
    
    
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:    "+space2+std::to_string(m_level));
    
    
    temp=m_rowsLeft/10;
    digits=0;
    while (temp) {
        temp /= 10;
        digits++;
    }
    string space3;
    for (int i=5; i>=digits; i--)
    {
        space3=space3+' ';
    }
    
    
    
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: "+space3+std::to_string(m_rowsLeft));
    
    
    
}

//difference between redisplaypiece and displaypiece is whether it's the first piece in the current level. 

void Game::redisplayPiece(int orientation, int &posx, int & posy)
{
   
    bool *pie=m_piece;
    //let the pointer go to the corresponding oritentaion.
    
    
    //pos x and pos y is the position of the most left and highest block of each 4X4 shape.
    
    
    
    
    
    
    switch (orientation) {
        case 0:
            
            break;
        case 1:
            pie=pie+16;
            break;
        case 2:
            pie=pie+32;
            break;
        case 3:
            pie=pie+48;
            break;
        default:
            break;
    }
    
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            if (*pie)
                shape[k][i]='#';
            else
                shape[k][i]=' ';
            
            pie++;
        }
        
    }
    
    
    
    
    
    //put it in the tank and screen!
    for(int i=0; i<4; i++)
    {
        
        for (int k=0; k<4; k++)
        {
            
           
            if(shape[k][i]=='#')
            {
                m_screen.gotoXY(k+posx,i+posy);
                m_tank.input1(k+posx, i+posy, '#');
                m_screen.printChar(shape[k][i]);
            }
            
            
        }
        
    }
    
    
    
    
    m_screen.refresh();
    
    
}

void Game::displayPiece(int orientation, int &posx, int & posy)
{
    
    ///////put all the chars into the tank!!!
    
    
    
    Piece *p=genPiece();
    bool *pie=p->shape();
    
    currentype=p->getType();
    
    m_piece=pie;
    
    if (firstPiece==false)
    {
    
        if(m_next!=nullptr)
        {
            pie=m_next;
            m_piece=m_next;  //hey, like the linked list!
            m_next=nullptr;
            currentype=beforeType;
            beforeType=0;
            
        }
        
    }
    
     //let the pointer go to the corresponding oritentaion.
    
    
    //pos x and pos y is the position of the most left and highest block of each 4X4 shape.
    
    
    switch (orientation) {
        case 0:
           
            break;
        case 1:
            pie=pie+16;
            break;
        case 2:
            pie=pie+32;
            break;
        case 3:
            pie=pie+48;
            break;
        default:
            break;
    }
    
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            if (*pie)
                shape[k][i]='#';
            else
                shape[k][i]=' ';
            
            pie++;
        }
        
    }
    
 
    
    //put it in the tank and screen!
    for(int i=0; i<4; i++)
    {
        
        for (int k=0; k<4; k++)
        {

            
            if(shape[k][i]=='#')
            {
                
                m_screen.gotoXY(k+posx,i+posy);
                
                if(m_tank.access(k+posx, i+posy)=='#' || m_tank.access(k+posx, i+posy)=='$')
                    endGame=true;
                
                m_tank.input1(k+posx, i+posy, '#');
                m_screen.printChar(shape[k][i]);
                
            }
            
            
        }
        
    }
    
    

    m_screen.refresh();
    
    
    
}
void Game::toDollar(int posx, int posy)
{
    ///for the special type:
    ///for Vapor!!!
    if (currentype==1)
    {
     
        //upper part!
        if (m_tank.access(posx+1, posy-1)=='$' || m_tank.access(posx+1, posy-1)=='*')
        {
            m_tank.input1(posx+1, posy-1,' ');
            m_screen.gotoXY(posx+1, posy-1);
            m_screen.printChar(' ');
        }
        
        if (m_tank.access(posx+2, posy-1)=='$' || m_tank.access(posx+2, posy-1)=='*')
        {
            m_tank.input1(posx+2, posy-1,' ');
            m_screen.gotoXY(posx+2, posy-1);
            m_screen.printChar(' ');
            
        }
        
        if (m_tank.access(posx+2, posy-2)=='$' || m_tank.access(posx+2, posy-2)=='*')
        {
            m_tank.input1(posx+2, posy-2,' ');
            m_screen.gotoXY(posx+2, posy-2);
            m_screen.printChar(' ');
            
        }
        
        if (m_tank.access(posx+1, posy-2)=='$' || m_tank.access(posx+1, posy-2)=='*')
        {
            m_tank.input1(posx+1, posy-2,' ');
            m_screen.gotoXY(posx+1, posy-2);
            m_screen.printChar(' ');
            
        }
        
        //lower part!
        if (m_tank.access(posx+1, posy+1)=='$' || m_tank.access(posx+1, posy+1)=='*')
        {
            m_tank.input1(posx+1, posy+1,' ');
            m_screen.gotoXY(posx+1, posy+1);
            m_screen.printChar(' ');
        }
        
        if (m_tank.access(posx+2, posy+1)=='$' || m_tank.access(posx+2, posy+1)=='*')
        {
            m_tank.input1(posx+2, posy+1,' ');
            m_screen.gotoXY(posx+2, posy+1);
            m_screen.printChar(' ');
            
        }
        
        if (m_tank.access(posx+2, posy+2)=='$' || m_tank.access(posx+2, posy+2)=='*')
        {
            m_tank.input1(posx+2, posy+2,' ');
            m_screen.gotoXY(posx+2, posy+2);
            m_screen.printChar(' ');
            
        }
        
        if (m_tank.access(posx+1, posy+2)=='$' || m_tank.access(posx+1, posy+2)=='*')
        {
            m_tank.input1(posx+1, posy+2,' ');
            m_screen.gotoXY(posx+1, posy+2);
            m_screen.printChar(' ');
            
        }
        
    
        
        
        
        
    }
    
    
    
    
    ///change them into dollars.
    for(int i=0; i<4; i++)
    {
        
        for (int k=0; k<4; k++)
        {
            
            
            if(shape[k][i]=='#')
            {
                m_tank.input1(posx+k, posy+i, '$');
                m_screen.gotoXY(posx+k, posy+i);
                m_screen.printChar('$');
            }
            
        }
        
    }
    
    //for vapor as well.
    if(currentype==1)
    {
        //itself
        if (m_tank.access(posx+1, posy)=='$' || m_tank.access(posx+1, posy)=='*')
        {
            m_tank.input1(posx+1, posy,' ');
            m_screen.gotoXY(posx+1, posy);
            m_screen.printChar(' ');
        }
        
        if (m_tank.access(posx+2, posy)=='$' || m_tank.access(posx+2, posy)=='*')
        {
            m_tank.input1(posx+2, posy,' ');
            m_screen.gotoXY(posx+2, posy);
            m_screen.printChar(' ');
            
        }
    }

    
    //for foam.
    if (currentype==2)
    {
        tempx=posx+1;
        tempy=posy+1;
        exeFoam(posx+1, posy+1);
        if(ifremove())
            remove();
        
    }
    
    //currenttype is the indentifier for special pieces.
    currentype=0;
}





bool *Game::getPiece()
{
    bool *pie=genPiece()->shape();

    return pie;
}




void Game::undisplay(int posx, int posy)
{
    
    //for screen
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            if (shape[k][i]=='#')
            {
                m_screen.gotoXY(posx+k, posy+i);
                m_screen.printChar(' ');
                m_tank.input1(posx+k, posy+i, ' ');

          
            }
            
        }
        
    }
    

    
    
    m_screen.refresh();
    
}

bool Game::playOneLevel()
{
    firstPiece=true;
    int orientation=0;
    int row=0;
    int posx=m_width/2-1;
    int posy=0;
    reachE=true;
    m_rowsLeft=5*m_level;
    m_time=std::max(100,1000-(100*(m_level-1)));
   
    
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    
   
    
    getNext();
    nextPiece();
    
    displayStatus();

  
    
        for (;;)
        {
          
            
            
            if(!reachE)
                redisplayPiece(orientation, posx, posy);
            else
            {
                displayPiece(orientation, posx, posy);
                reachE=false;
                
                if (!firstPiece)
                {
                    unNext();
                    getNext();
                    nextPiece();
                }
            }
            
            
            if (endGame)
                return false;
          
            int  endTime = getMsecSinceStart() + m_time;
            // Repeat as long as current time has not yet reached the end time
            while (getMsecSinceStart() < endTime)
            {
                int temp=orientation;
                char ch;
                if (getCharIfAny(ch))
                {
                    // There was a character typed; it's now in ch
                    //check keyboard input.
                    
                    if (currentype!=3)
                    {
                        switch (ch)
                        {
                            case ' ':
                                while(1)
                                {
                                    if (canMove(2,posx,posy))
                                    {
                                        undisplay(posx, posy);

                                        posy++;
                                        
                                        redisplayPiece(orientation, posx, posy);
                                    }
                                    else
                                        break;
                                }
                                
                                break;
                                
                                
                            case ARROW_LEFT:
                                
                                undisplay(posx, posy);
                                
                                if (canMove(0,posx,posy))
                                    posx--;
                                    
                                redisplayPiece(orientation, posx, posy);
                                break;
                                
                            case ARROW_DOWN:
                                
                                undisplay(posx, posy);
                                
                                if(canMove(2, posx, posy))
                                {
                                    posy++;
                                }
                                
                            
                                
                                redisplayPiece(orientation, posx, posy);
                                
                                break;
                            case ARROW_RIGHT:
                                
                                undisplay(posx, posy);
                                
                                if (canMove(1,posx,posy))
                                    posx++;
                                
                                redisplayPiece(orientation, posx, posy);
                                break;
                                
                                
                            case ARROW_UP:
                                undisplay(posx, posy);
                                
                                temp=(orientation+1)%4;
                                
                                if(canRotate(temp, posx, posy))
                                {
                                    
                                    orientation++;
                                    
                                    orientation=orientation%4;
                                }
                                    redisplayPiece(orientation, posx, posy);
                                
                                
                                break;
                            
                           
                                
                           case 'q':
                                endGame=true;
                                return false;
                                break;
                           case 'Q':
                                endGame=true;
                                return false;
                                
                                break;
                                
                            default:
                                break;
                        }
                    
                    }
                    
                    else
                    {
                        
                        
                        switch (ch)
                        {
                            case ' ':
                                while(1)
                                {
                                    if (canMove(2,posx,posy))
                                    {
                                        undisplay(posx, posy);
                                        
                                        posy++;
                                        
                                        redisplayPiece(orientation, posx, posy);
                                    }
                                    else
                                        break;
                                }
                                
                                break;
                                
                                
                            case ARROW_LEFT:
                                
                                undisplay(posx, posy);
                                
                                if (canMove(1,posx,posy))
                                    posx++;
                                
                                redisplayPiece(orientation, posx, posy);
                                break;
                                
                            case ARROW_DOWN:
                                
                                undisplay(posx, posy);
                                
                                if(canMove(2, posx, posy))
                                {
                                    posy++;
                                }
                                
                                
                                
                                redisplayPiece(orientation, posx, posy);
                                
                                break;
                            case ARROW_RIGHT:
                                
                                undisplay(posx, posy);
                                
                                if (canMove(0,posx,posy))
                                    posx--;
                                
                                redisplayPiece(orientation, posx, posy);
                                break;
                                
                                
                            case ARROW_UP:
                                undisplay(posx, posy);
                                
                                temp=(orientation+1)%4;
                                
                                if(canRotate(temp, posx, posy))
                                {
                                    
                                    orientation++;
                                    
                                    orientation=orientation%4;
                                }
                                redisplayPiece(orientation, posx, posy);
                                
                                
                                break;
                                
                                
                                
                            case 'q':
                                endGame=true;
                                return false;
                                break;
                            case 'Q':
                                endGame=true;
                                return false;
                                
                                break;
                                
                            default:
                                break;
                        }

                        
                        
                        
                    }
                    
                    
                    
                    
                    
                    
                    
                }
                
                if (reachE)
                {
                    //if we force it to reach end.
                    
                    firstPiece=false;

                    toDollar(posx, posy);
                    posx=m_width/2-1;
                    posy=0;
                    orientation=0; //put orientaion back.
                    
                    if(ifremove())
                    {
                        
                        remove();
                        
                        
                        row++;
                        /////////this part is to calculate the score!
                    switch (m_rowChanged)
                        {
                            case 0:
                                
                                break;
                                
                            case 1:
                                m_points=m_points+100;
                                break;
                            case 2:
                                
                                m_points=m_points+200;
                                break;
                            case 3:
                                
                                m_points=m_points+400;
                                break;
                            case 4:
                                m_points=m_points+800;
                                break;
                            case 5:
                                m_points=m_points+1600;
                                //assumption, this won'be reached.
                            default:
                                break;
                        }
                          m_rowsLeft=m_rowsLeft-m_rowChanged;
                        if (m_rowsLeft<0)
                            m_rowsLeft=0;
                        
                        displayStatus();
                        
                        if (m_rowsLeft<=0)
                        {
                            m_level++;
                            return true;
                        }
                    }
                    
              
                    
                    
                    
                    
                    
                    break;
                }
                
            }
            
            if(!reachE)
            {
                undisplay(posx, posy);
                //move the piece down by one.
                if(canMove(2, posx, posy))
                {
                   
                    posy++;
                    redisplayPiece(orientation, posx, posy);
                }
                
                //if it naturally reach to the end.
                else
                {
                
                    
                    firstPiece=false;
                    
                    toDollar(posx, posy);
                    posx=m_width/2-1;
                    posy=0;
                    orientation=0; //put orientaion back.
                    
                    if(ifremove())
                    {
                        
                        remove();
                        
                        
                        row++;
                        /////////this part is to calculate the score!
                        switch (m_rowChanged)
                        {
                            case 0:
                                
                                break;
                                
                            case 1:
                                m_points=m_points+100;
                                break;
                            case 2:
                                
                                m_points=m_points+200;
                                break;
                            case 3:
                                
                                m_points=m_points+400;
                                break;
                            case 4:
                                m_points=m_points+800;
                                break;
                            case 5:
                                m_points=m_points+1600;
                                //assumption, this won'be reached.
                            default:
                                break;
                        }
                        m_rowsLeft=m_rowsLeft-m_rowChanged;
                        displayStatus();
                        if (m_rowsLeft<=0)
                        {
                            m_level++;
                            return true;
                        }
                        
                        
                       
                    }
                    

                    
                    
                    
                }
               
            }
            
            //check if we should end the game?
            else
            {
                    if (endGame)
                        return false;
           
                
            }
            
           
        }
    
    //should never reach here, but anyway.
    
    m_time=std::max(100,1000-(100*(m_level-1)));
 
    if (m_rowsLeft==0)
        return true;
    else
        return false;
}

//generate some pieces.
Piece* Game::genPiece ()
{
    Piece *imitris;
    switch (randPieceType())    //what about num_piece_types?
	{
        case PIECE_I:
            imitris=new Ipiece;
            
            break;
            
            
        case PIECE_L:
            imitris=new Lpiece;
            break;
            
        case PIECE_J:
            imitris=new Jpiece;
            break;
            
        case PIECE_CRAZY:
            imitris=new crazy;
            break;
            
        case PIECE_O:
            imitris=new Opiece;
            break;
            
        case PIECE_FOAM:
            imitris=new foam;
            break;
            
        case PIECE_S:
            imitris=new Spiece;
            break;
            
        case PIECE_T:
            imitris=new Tpiece;
            break;
            
        case PIECE_VAPOR:
            imitris=new vapor;
            break;
            
        case PIECE_Z:
            imitris=new Zpiece;
            break;
            
        default:
            imitris=nullptr; //will never encounter.
            break;
            
            
    }
    return imitris;
}

void Game::changePoints(int increase)
{
    m_points=m_points+increase;
}


//whether the piece can move or not.
bool Game::canMove(int direction, int posx, int posy)
{
    // left:0
    // right:1
    // down:2
    
    if (direction==1)
    {
        int largest[4]={-1,-1,-1,-1}; //initialize the array
        
        for(int i=0; i<4; i++)
        {
            
            for (int k=0; k<4; k++)
            {
                if(shape[k][i]=='#' )
                    largest[i]=k;
                
                
                
            }
            
        }
     
        for(int i=0; i<4; i++)
        {
            if (largest[i]>=0)
            {
                if(m_tank.access(posx+largest[i]+1, posy+i)=='@' || m_tank.access(posx+largest[i]+1, posy+i)=='$' || m_tank.access(posx+largest[i]+1, posy+i)=='*')
                    return false;
            }
            
        }

        
    }
    
    if (direction==0)
    {
        int smallest[4]={-1,-1,-1,-1};
        
        for(int i=0; i<4; i++)
        {
            
            for (int k=3; k>=0; k--)
            {
                if(shape[k][i]=='#')
                    smallest[i]=k;
                
            }
            
        }
        
        for(int i=0; i<4; i++)
        {
          if (smallest[i]>=0)
          {
            if(m_tank.access(posx+smallest[i]-1, posy+i)=='@' || m_tank.access(posx+smallest[i]-1, posy+i)=='$' ||  m_tank.access(posx+smallest[i]-1, posy+i)=='*' )
                return false;
          }
            
        }

        
    }
    
    if (direction==2)
    {
        int down[4]={-1,-1,-1,-1};  // it used to be all zeros.
        
        for(int i=0; i<4; i++)
        {
            
            for (int k=0; k<4; k++)
            {
                if(shape[i][k]=='#')
                    down[i]=k;
                
            }
            
        }
        
       
        
        for(int i=0; i<4; i++)
        {
            if(down[i]>=0)
            
                if(m_tank.access(posx+i, posy+down[i]+1)=='@' || m_tank.access(posx+i,posy+down[i]+1 )=='$' || m_tank.access(posx+i, posy+down[i]+1)=='*')
                {
                    
                    reachE=true;
                    
                    return false;
                }
            
        }
        
        
        
    }
    
    
    
    
    
    
    return true;
}

//a test function

void Game::test()
{
    m_screen.gotoXY(3, 4);
    m_screen.printChar('T');
    m_screen.refresh();
    
}

//get the next piece, before type is the currenttype for next piece.

void Game::getNext()
{
    Piece *temp=genPiece();
    m_next=temp->shape();
    beforeType=temp->getType();
    
    
}


//display the next piece.
void Game::nextPiece()
{
    
  
    
    char nextP[4][4];
    bool *temp=m_next;
    
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            if (*temp)
                nextP[k][i]='#';
            else
                nextP[k][i]=' ';
            
            temp++;
        }
        
    }
    
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            m_screen.gotoXY(NEXT_PIECE_X+k, NEXT_PIECE_Y+i);
            
            if(nextP[k][i]=='#')
            m_screen.printChar(nextP[k][i]);
            
            
        }
        
    }
    
}


//undisplay next
void Game::unNext()
{
    
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            m_screen.gotoXY(NEXT_PIECE_X+i, NEXT_PIECE_Y+k);
            
          
            m_screen.printChar(' ');
            
        }
        
    }
    
}


//remove one or multiple rows.
bool Game::ifremove()
{
    int counter=0;
    int j=0;
    
    for (int k=0 ; k<m_height; k++)
    {
        for (int i=1; i<=m_width; i++)
        {
        
            if (m_tank.access(i, k)=='$' || m_tank.access(i, k)=='*')
                counter++;
            
            if (counter==m_width)
            {
                m_row[j]=k;
                j++;
                
                
            }
            
        }
        counter=0;
    }
    
    if (j>0)
        return true;
    
    return false;
}

void Game::remove()
{
    char a;
    m_rowChanged=0;
    //counting the four different posibilities.
    if (m_row[0]>0)
    {
        m_rowChanged=1;
        for (int k=m_row[0]-1; k>=1; k--)
        {
            
            for (int i=1; i<m_width; i++)
            {
                
                a=m_tank.access(i, k);
                
                m_tank.input1(i, k+1, a);
                
                
                m_screen.gotoXY(i, k+1);
                m_screen.printChar(a);
                
                
                
                
                
            }
            

        }
    }
    if (m_row[1]>0)
    {
        m_rowChanged=2;
        for (int k=m_row[1]-1; k>=1; k--)
        {
            
            for (int i=1; i<m_width; i++)
            {
                
                a=m_tank.access(i, k);
                
                m_tank.input1(i, k+1, a);
                
                
                m_screen.gotoXY(i, k+1);
                m_screen.printChar(a);
                
                
                
                
                
            }
            
            
        }
    }
    
    
    if (m_row[2]>0)
    {
        m_rowChanged=3;
        for (int k=m_row[2]-1; k>=1; k--)
        {
            
            for (int i=1; i<m_width; i++)
            {
                
                a=m_tank.access(i, k);
                
                m_tank.input1(i, k+1, a);
                
                
                m_screen.gotoXY(i, k+1);
                m_screen.printChar(a);
                
                
                
                
                
            }
            
            
        }
    }
    
    if (m_row[3]>0)
    {
        m_rowChanged=4;
        for (int k=m_row[3]-1; k>=1; k--)
        {
            
            for (int i=1; i<m_width; i++)
            {
                
                a=m_tank.access(i, k);
                
                m_tank.input1(i, k+1, a);
                
                
                m_screen.gotoXY(i, k+1);
                m_screen.printChar(a);
                
                
                
                
                
            }
            
            
        }
    }
    
    if (m_row[4]>0)
    {
        m_rowChanged=5;
        for (int k=m_row[4]-1; k>=1; k--)
        {
            
            for (int i=1; i<m_width; i++)
            {
                
                a=m_tank.access(i, k);
                
                m_tank.input1(i, k+1, a);
                
                
                m_screen.gotoXY(i, k+1);
                m_screen.printChar(a);
                
                
                
                
                
            }
            
            
        }
    }
    
    
    m_screen.refresh();
}


//check whether the piece can rotate or not.


bool Game::canRotate(int orientation, int posx, int posy)
{
    bool*pie=m_piece;
    
    switch (orientation) {
        case 0:
            
            break;
        case 1:
            pie=pie+16;
            break;
        case 2:
            pie=pie+32;
            break;
        case 3:
            pie=pie+48;
            break;
        default:
            break;
    }
    
    char temp[4][4];
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<4; k++)
        {
            if (*pie)
                temp[k][i]='#';
            else
                temp[k][i]=' ';
            
            pie++;
        }
        
    }
    
 
    
    //put it in the tank and screen!
    for(int i=0; i<4; i++)
    {
        
        for (int k=0; k<4; k++)
        {
            
            
            if(temp[k][i]=='#' && m_tank.access(k+posx, i+posy)=='@' )
            {
                
                  return false;
            }
              
                
            if(temp[k][i]=='#' && m_tank.access(k+posx, i+posy)=='*' )
            {
                
                return false;
            }
            
            if(temp[k][i]=='#' && m_tank.access(k+posx, i+posy)=='$' )
            {
                
                return false;
            }
            
            
            
        }
        
    }
    
    
    
    
    
    return true;
    

    
    
}



//this is the recursion function for foam piece.

void Game::exeFoam(int x, int y)
{
    m_tank.input1(x, y, '*');
    m_screen.gotoXY(x, y);
    m_screen.printChar('*');
    
    
    
   
    
    
   //recursion
    if (m_tank.access(x, y-1)==' ' && y-1>=tempy-2)
    {
        
        exeFoam(x, y-1);
        
    }
   
     if (m_tank.access(x, y+1)==' ' && y+1<=tempy+2)
    {
        
        exeFoam(x, y+1);
        
        
    }

    if (m_tank.access(x+1, y)==' ' && x+1<=tempx+2)
    {
        
        exeFoam(x+1, y);
        
    }
    
   
  
    
    if (m_tank.access(x-1, y)==' ' && x-1>=tempx-2)
    {
        
        exeFoam(x-1, y);
    }
    
    
    
    
    
    
    return;
    
}

