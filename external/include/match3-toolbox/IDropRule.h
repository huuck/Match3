#pragma once
#include <vector>
#include "IBoard.h"
#include "TileWaypointVO.h"

class IDropRule
{
public:
	IDropRule();

	virtual std::vector<TileWaypointVO*> applyTo(IBoard* board_) = 0;
	virtual bool isBoardStable(IBoard* board_) = 0;

	virtual ~IDropRule();
};

