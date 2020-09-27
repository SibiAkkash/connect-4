#include <iostream>
#include <vector>

using namespace std;

bool isCellWithinBoundaries(int i, int j)
{
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}

int checkSlice(vector<vector<int>> board, int row, int col, pair<int, int> incr)
{
    // check for contiguous block of 4 from cell(row, col) in slice
    int count = 0;
    int prev = board[row][col];
    // next cell
    row += incr.first;
    col += incr.second;
    while (isCellWithinBoundaries(row, col))
    {
        // cout << board[i][j] << " ";
        if (board[row][col] == prev)
        {
            count++;
            row += incr.first;
            col += incr.second;
        }
        else
        {
            break;
        }
    }
    return count;
}

int main()
{
    vector<vector<int>> board = {
        {0, 0, 1, 1, 1, 2, 2, 0},
        {0, 1, 1, 1, 1, 2, 2, 1},
        {2, 2, 2, 0, 0, 1, 1, 1}
    };
    int l = checkSlice(board, 2, 5, pair<int, int>(0, -1));
    int r = checkSlice(board, 2, 5, pair<int, int>(0, 1));
    
    cout << l + 1 + r << endl;
   
}