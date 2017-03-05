#pragma once
#include "IDropRule.h"
class GravityDropper :
	public IDropRule
{
public:
	GravityDropper();

	std::vector<TileWaypointVO*> applyTo(IBoard* board_);
	bool isBoardStable(IBoard* board_);

	~GravityDropper();
};

