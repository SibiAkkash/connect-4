#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

Board::Board()
{
    board.resize(this->ROWS, vector<int>(this->COLS, 0));
}

void Board::showBoard()
{
    for (int i = 0; i < this->ROWS; i++)
    {
        for (int j = 0; j < this->COLS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::makeMove(int row, int col, char player)
{
    // check row, col, player, cell occupancy
    if (row < 0 && row >= this->ROWS)
    {
        cout << "Row out of bounds";
    }
    else if (col < 0 && col >= this->COLS)
    {
        cout << "Col out of bounds";
    }
    else if (player != 1 && player != 2)
    {
        cout << "Invalid player";
    }
    else if (board[row][col])
    {
        cout << "Cell is already full";
    }
    else
    {
        board[row][col] = player;
    }
}

bool Board::checkColumn(int row, int col, char player)
{
    // columns -> check the 3 coins below the current cell
    if (row >= 3 &&
        board[row - 1][col] == player &&
        board[row - 2][col] == player &&
        board[row - 2][col] == player)
    {
        return true;
    }
    return false;
}

bool Board::checkRow(int row, int col, char player)
{
    // rows : check whether there are 4 consecutive coins of the same player as part of the current move
    // Eg: OXX(X)OXX -> not a win
    // Eg: OOX(X)XXO -> win
    int left = col - 1;
    int right = col + 1;
    int count = 1; // one is the current move
    bool leftDone = false;
    bool rightDone = false;

    while (left >= 0 || right < this->COLS)
    {
        leftDone = board[row][left] != player;
        rightDone = board[row][right] != player;
        if (!leftDone)
        {
            left--;
            count++;
        }
        if (!rightDone)
        {
            right++;
            count++;
        }
        if (count >= 4 || (leftDone && rightDone))
        {
            break;
        }
    }
    return count >= 4;
}

bool Board::checkDiagonals(int row, int col, char player)
{
    /* 
        X   -   X   -   X
        O  (X)  X   X   O
        O   O   X   O   X
        O   O   O   X   O
    */
    int mainCount = 1;
    int oppCount = 1;
    pair<int, int> topLeft(row - 1, col - 1);
    pair<int, int> bottomRight(row + 1, col + 1);
    pair<int, int> topRight(row - 1, col + 1);
    pair<int, int> bottomLeft(row + 1, col - 1);
    bool topLeftDone = false;
    bool bottomRightDone = false;
    bool topRightDone = false;
    bool bottomLeftDone = false;

    while ((topLeft.first >= 0 && topLeft.second >= 0) ||
           (bottomRight.first < this->ROWS && bottomRight.second < this->COLS) ||
           (topRight.first >= 0 && topRight.second < this->COLS) ||
           (bottomLeft.first < this->ROWS && bottomLeft.second >= 0))
    {
        topLeftDone = board[topLeft.first][topLeft.second] != player;
        bottomRightDone = board[bottomRight.first][bottomRight.second] != player;
        topRightDone = board[topRight.first][topRight.second] != player;
        bottomLeftDone = board[bottomLeft.first][bottomLeft.second] != player;

        if (!topLeftDone)
        {
            topLeft.first--;
            topLeft.second--;
            mainCount++;
        }
        if (!bottomRightDone)
        {
            bottomRight.first++;
            bottomRight.second++;
            mainCount++;
        }
        if (!topRightDone)
        {
            topRight.first--;
            topRight.second++;
            oppCount++;
        }
        if (!bottomLeftDone)
        {
            bottomLeft.first++;
            bottomLeft.second--;
            oppCount++;
        }

        if (mainCount >= 4 || oppCount >= 4 || (topLeftDone && bottomRightDone && topRightDone && bottomLeftDone))
        {
            break;
        }
    }
    return mainCount >= 4 || oppCount >= 4;
}

bool Board::checkWin(int row, int col, char player)
{
    return this->checkColumn(row, col, player) || this->checkRow(row, col, player) || this->checkDiagonals(row, col, player);
}
