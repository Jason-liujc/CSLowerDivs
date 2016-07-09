
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Colosseum;




class Player
{
public:
    // Constructor
    Player(Colosseum *colosseum, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    std::string move(int dir);
    std::string push();
    void   setDead();
    
private:
    Colosseum* m_colosseum;
    int    m_row;
    int    m_col;
    bool   m_dead;
};


#endif