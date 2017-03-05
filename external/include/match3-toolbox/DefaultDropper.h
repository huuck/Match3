#pragma once
#include "TileDropper.h"
class DefaultDropper :
	public TileDropper
{
public:
	DefaultDropper(IBoard* board_);

	~DefaultDropper();
};

