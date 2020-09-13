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
            int cell = board[i][j];
            switch (cell)
            {
            case 0:
                cout << "\x1B[90m" << cell << "\033[0m ";
                break;
            case 1:
                cout << "\x1B[31m" << cell << "\033[0m ";
                break;
            case 2:
                cout << "\x1B[34m" << cell << "\033[0m ";
                break;
            }
        }
        cout << endl;
    }
}

bool Board::isCellWithinBoundaries(int row, int col)
{
    return row >= 0 && row < this->ROWS && col >= 0 && col < this->COLS;
}

bool Board::isPlayerCell(pair<int, int> cell, int player)
{
    return this->isCellWithinBoundaries(cell.first, cell.second) &&
           this->board[cell.first][cell.second] == player;
}

int Board::makeMove(int col, int player)
{
    int row = 0;
    // check row, col, player, cell occupancy
    if (col < 0 && col >= this->COLS)
    {
        cout << "Col out of bounds" << endl;
    }
    else if (player != 1 && player != 2)
    {
        cout << "Invalid player" << endl;
    }
    else if (board[0][col])
    {
        cout << "Column is already full" << endl;
    }
    else
    {
        while (row < this->ROWS && !board[row][col])
        {
            row++;
        }
        row--;
        board[row][col] = player;
    }
    // append to moves list
    this->moves.push_back(pair<int, int>(row, col));
    // return win ?
    return this->checkWin(row, col, player) ? player : 0;
}


void Board::undoMove()
{
    // get latest move
    pair<int, int> lastMove = this->moves.back();
    int row = lastMove.first;
    int col = lastMove.second;
    // set cell to empty
    board[row][col] = 0;
    // pop last move
    this->moves.pop_back();
}

bool Board::checkColumn(int row, int col, int player)
{
    if (row <= 2 &&
        board[row + 1][col] == player &&
        board[row + 2][col] == player &&
        board[row + 3][col] == player)
    {
        return true;
    }
    return false;
}

bool Board::checkRow(int row, int col, int player)
{
    // check whether there are 4 consecutive coins of the same player as part of the current move
    // Eg: OXX(X)OXX -> not a win
    // Eg: OOX(X)XXO -> win
    int left = col - 1;
    int right = col + 1;
    int count = 1; // one is the current move
    bool canCheckLeft = false;
    bool canCheckRight = false;

    while (left >= 0 || right < this->COLS)
    {
        canCheckLeft = this->isPlayerCell(pair<int, int>(row, left), player);
        canCheckRight = this->isPlayerCell(pair<int, int>(row, right), player);
        if (canCheckLeft)
        {
            left--;
            count++;
        }
        if (canCheckRight)
        {
            right++;
            count++;
        }
        if (count >= 4 || (!canCheckLeft && !canCheckRight))
        {
            break;
        }
    }
    return count >= 4;
}

bool Board::checkDiagonals(int row, int col, int player)
{
    /* 
        X   -   X   -   X
        O   X   X   X   O
        O   O  (X)  O   X
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
        topLeftDone = this->isPlayerCell(topLeft, player);
        bottomRightDone = this->isPlayerCell(bottomRight, player);
        topRightDone = this->isPlayerCell(topRight, player);
        bottomLeftDone = this->isPlayerCell(bottomLeft, player);

        if (topLeftDone)
        {
            topLeft.first--;
            topLeft.second--;
            mainCount++;
        }
        if (bottomRightDone)
        {
            bottomRight.first++;
            bottomRight.second++;
            mainCount++;
        }
        if (topRightDone)
        {
            topRight.first--;
            topRight.second++;
            oppCount++;
        }
        if (bottomLeftDone)
        {
            bottomLeft.first++;
            bottomLeft.second--;
            oppCount++;
        }

        if (mainCount >= 4 ||
            oppCount >= 4 ||
            (!topLeftDone && !bottomRightDone && !topRightDone && !bottomLeftDone))
        {
            break;
        }
    }
    return mainCount >= 4 || oppCount >= 4;
}

bool Board::checkWin(int row, int col, int player)
{
    return this->checkColumn(row, col, player) || this->checkRow(row, col, player) || this->checkDiagonals(row, col, player);
}

int Board::findBestMove()
{
    int bestCol = 0;
    int bestScore = INT_MIN;
    int maxDepth = 2;
    // for all possible moves, get score from minmax
    // if score > bestScore, update bestScore and bestCol
    int player = 2; // AI id
    for (int i = 0; i < this->COLS; i++)
    {
        // check whether col is empty
        bool isColumnEmpty = board[0][i] == 0;
        if (isColumnEmpty)
        {
            // make move in the col
            this->makeMove(i, player);
            // get score
            int score = this->minimax(1, maxDepth, false, player, 0);
            // update score
            if (score > bestScore)
            {
                bestScore = score;
                bestCol = i;
            }
            // undo move
            this->undoMove();
        }
    }
    return bestCol;
}

int Board::minimax(int currDepth, int maxDepth, bool isMaximizingPlayer, int player, int tabs)
{
    // evaluate board for leaf nodes
    if (currDepth == maxDepth)
    {
        for(int i = 0; i < tabs; i++) cout << "\t";
        // cout << "leaf node, evalutaing board....." << "\t";
        return this->evalBoard();
    }
    int nextPlayer = player == 1 ? 2 : 1;
    if (isMaximizingPlayer)
    {
        int bestScore = INT_MIN;
        for(int i = 0; i < this->COLS; i++) {
            bool isColumnEmpty = board[0][i] == 0;
            if(isColumnEmpty) {
                // simulate move in each column
                this->makeMove(i, player);
                // get score
                int score = this->minimax(currDepth + 1, maxDepth, false, nextPlayer, tabs+1);
                // update score
                bestScore = max(bestScore, score);


                for(int i = 0; i < tabs; i++) cout << "\t";
                cout << "max player " << score << " " << bestScore << endl;


                // undo move
                this->undoMove();

            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for(int i = 0; i < this->COLS; i++) {
            bool isColumnEmpty = board[0][i] == 0;
            if(isColumnEmpty) {
                // simulate move in each column
                this->makeMove(i, player);
                // get score
                int score = this->minimax(currDepth + 1, maxDepth, true, nextPlayer, tabs+1);
                // update score
                bestScore = min(bestScore, score);


                for(int i = 0; i < tabs; i++) cout << "\t";
                cout << "min player " << score << " " << bestScore << endl;


                // undo move
                this->undoMove();
            }
        }
        cout << endl << endl;
        return bestScore;
    }
}

int Board::evalBoard()
{

    return rand() % (7);
}
