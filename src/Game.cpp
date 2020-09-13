#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;

Game::Game()
{
	Board board;
	this->currentPlayer = 1;
	this->gameOver = false;
}

void Game::start() {
	this->loop();
}

void Game::togglePlayer()
{
	this->currentPlayer = this->currentPlayer == 1 ? 2 : 1;
}

void Game::loop()
{
	while (!this->gameOver)
	{
		cout << "Player " << this->currentPlayer << ": ";

		if(this->currentPlayer == 1) {
			//human
			int move;
			cin >> move;
			this->gameOver = board.makeMove(move, this->currentPlayer);
		}
		if(this->currentPlayer == 2) {
			// ai
			int move = board.findBestMove();
			cout << "best ai move: " << move << endl;
			this->gameOver = board.makeMove(move, this->currentPlayer);
		}

		board.showBoard();

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
	g.start();
	return 0;
}