#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;

Game::Game()
{
	Board board;
	this->currentPlayer = 1;
	this->gameOver = false;
	this->loop();
}

void Game::togglePlayer()
{
	this->currentPlayer = this->currentPlayer == 1 ? 2 : 1;
}

// 1. Get move from current player
// 2. send to board, get win result
// continue/stop loop
void Game::loop()
{
	while (!this->gameOver)
	{
		int move;
		cout << "Player " << this->currentPlayer << ": ";
		cin >> move;
		int win = board.makeMove(move, this->currentPlayer);
		this->gameOver = win;
		if (this->gameOver)
		{
			winner = this->currentPlayer;
		}
		else
		{
			this->togglePlayer();
		}
	}
	cout << "Player " << winner << " won" << endl;
}

int main()
{
	Game g;
	return 0;
}