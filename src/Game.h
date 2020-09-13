#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "Board.h"

class Game
{
    int currentPlayer;
    Board board;
    int winner;
    bool gameOver;

public:
    // init board object, player
    Game();
    void loop();
    int findBestMove();

private:
    void togglePlayer();
};

#endif