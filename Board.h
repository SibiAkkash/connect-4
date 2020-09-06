#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include <vector>
using namespace std;

class Board
{
    const int ROWS = 6;
    const int COLS = 7;
    std::vector<std::vector<int>> board;

public:
    Board();
    void showBoard();
    void makeMove(int col, char player);

private:
    bool checkColumn(int row, int col, char player);
    bool checkRow(int row, int col, char player);
    bool checkDiagonals(int row, int col, char player);
    bool checkWin(int row, int col, char player);
};

#endif