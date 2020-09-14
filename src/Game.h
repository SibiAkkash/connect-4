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
    // game loop
    void loop();
    void start();
    int findBestMove();

private:
    void togglePlayer();
    /**
     * @param depth Current lookahead depth
     * @param maxDepth max lookahead depth
     * @param isMaximizingPlayer max player or not
     * @param player player symbol
     * @return player symbol if win else 0
    */
    int minimax(int depth, int maxDepth, bool isMaximizingPlayer, int player);
};

#endif