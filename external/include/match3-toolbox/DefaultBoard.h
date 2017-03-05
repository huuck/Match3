#pragma once
#include "IBoard.h"
#include "DefaultTile.h"
#include "StateMachine.h"
#include <vector>
class DefaultBoard :
	public IBoard
{
public:
	DefaultBoard(int width_ = 0, int height_ = 0);
	void printBoard();
	void remove(ITile * tile);
	ITile * getTileAt(int row_, int column_);

	DefaultTile * addTile(int row_, int column_, int type_);

	int getNumRows() { return _height; };
	int getNumColumns() { return _width; };

	void shiftBoardVertically(int numRows_);

	~DefaultBoard();
private:
	std::vector<ITile*> _tiles;

	int _width;
	int _height;
};

