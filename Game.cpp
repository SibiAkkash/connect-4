#include <iostream>
#include <vector>
#include "Board.h"
using namespace std;

int main() {
	Board board;
	board.makeMove(3, 1);
	board.makeMove(3, 2);
	board.makeMove(3, 2);
	board.showBoard();
	return 0;
}