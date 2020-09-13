#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include <vector>
using namespace std;

class Board
{
    const int ROWS = 6;
    const int COLS = 7;
    vector<vector<int>> board;

public:
    Board();
    void showBoard();
    /**
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return player symbol if win else 0
    */
    int makeMove(int col, int player);
    int evalBoard();

private:
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @return (`row`, `col) within boundaries of the board
     */
    bool isCellWithinBoundaries(int row, int col);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return column win
    */
    bool checkColumn(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return row win
    */
    bool checkRow(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return diagonals win
    */
    bool checkDiagonals(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return win from move cell
    */
    bool checkWin(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return if cell at (`row`, `col`) == player
    */
    bool isPlayerCell(pair<int, int> cell, int player);
};

#endif