#ifndef GAME_H
#define GAME_H


#include "Colosseum.h"




bool recommendMove(const Colosseum& colosseum, int r, int c, int& bestDir);
int computeDanger(const Colosseum& colosseum, int r, int c);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nVillains);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Colosseum* m_colosseum;
    
    // Helper functions
    std::string takePlayerTurn();
};

#endif