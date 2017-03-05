#pragma once
#include "ITile.h"

class IBoard
{
public:
	IBoard(int width_ = 0, int height_ = 0);

	virtual ITile* getTileAt(int x_, int y_) = 0;
	virtual int getNumRows() = 0;
	virtual int getNumColumns() = 0;

	virtual ~IBoard();
};

