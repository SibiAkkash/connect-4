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

void Game::start()
{
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

		if (this->currentPlayer == 1)
		{
			//human
			int move;
			cin >> move;
			this->gameOver = board.makeMove(move, this->currentPlayer);
		}
		if (this->currentPlayer == 2)
		{
			// ai
			int move = this->findBestMove();
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

int Game::findBestMove()
{
	int bestCol = 0;
	int bestScore = INT_MIN;
	int maxDepth = 2;
	int player = 2; // AI id
	for (int i = 0; i < board.getCols(); i++)
	{
		// can we play in this column ?
		if (board.isColumnEmpty(i))
		{
			// make move in the col
			board.makeMove(i, player);
			// get score
			int score = this->minimax(1, maxDepth, false, player);
			// update score
			if (score > bestScore)
			{
				bestScore = score;
				bestCol = i;
			}
			// undo move
			board.undoMove();
		}
	}
	return bestCol;
}

int Game::minimax(int depth, int maxDepth, bool isMaximizingPlayer, int player)
{
	if (depth == maxDepth)
	{
		return board.evaluateBoard(player);
	}

	int nextPlayer = player == 1 ? 2 : 1;

	if (isMaximizingPlayer)
	{
		int bestScore = INT_MIN;
		for (int i = 0; i < board.getCols(); i++)
		{
			// can we play in this column ?
			if (board.isColumnEmpty(i))
			{
				// simulate move in each column
				board.makeMove(i, player);
				// get score
				int score = minimax(depth + 1, maxDepth, false, nextPlayer);
				// update score
				bestScore = max(bestScore, score);
				// undo move
				board.undoMove();
				// cout << "max player " << score << " " << bestScore << endl;
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = INT_MAX;
		for (int i = 0; i < board.getCols(); i++)
		{
			// can we play in this column ?
			if (board.isColumnEmpty(i))
			{
				// simulate move in each column
				board.makeMove(i, player);
				// get score
				int score = this->minimax(depth + 1, maxDepth, true, nextPlayer);
				// update score
				bestScore = min(bestScore, score);
				// undo move
				board.undoMove();
				// cout << "min player " << score << " " << bestScore << endl;
			}
		}
		return bestScore;
	}
}

int main()
{
	Game g;
	g.start();
	return 0;
}