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
    int makeMove(int col, int player);

private:
    bool isWithinBoundaries(int row, int col);
    bool checkColumn(int row, int col, int player);
    bool checkRow(int row, int col, int player);
    bool checkDiagonals(int row, int col, int player);
    bool checkWin(int row, int col, int player);
    bool canCheckCell(pair<int, int> cell, int player);

};

#endif