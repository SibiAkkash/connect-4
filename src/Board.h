#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include <vector>
using namespace std;

class Board
{
    const int ROWS = 6;
    const int COLS = 7;
    vector<vector<int>> board;
    vector<pair<int, int>> moves;

public:
    Board();
    int getCols();
    int getRows();
    bool isColumnEmpty(int col);
    void showBoard();
    /**
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return player symbol if win else 0
    */
    int makeMove(int col, int player);
    void undoMove();
    /**
     * @param player player symbol
    */
    int evaluateBoard(int player);

private:
    int checkSlice(int row, int col, pair<int, int> incr); /**
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
    bool checkColumnWin(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return row win
    */
    bool checkRowWin(int row, int col, int player);
    /**
     * @param row Row index of move
     * @param col Column index of move
     * @param player symbol of player making the move
     * @return diagonals win
    */
    bool checkDiagonalsWin(int row, int col, int player);
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