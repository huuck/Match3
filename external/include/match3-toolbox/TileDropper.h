#pragma once
#include "IBoard.h"
#include "IDropRule.h"

class TileDropper
{
public:
	TileDropper(IBoard* board_);

	std::vector<TileWaypointVO*> dropTiles();
	bool isBoardStable();

	~TileDropper();

protected:
	std::vector<IDropRule*> _rules;
	virtual void setupRules();

private:
	IBoard* _board;
};

