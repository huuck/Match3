#pragma once
#include "ITile.h"
class TileWaypointVO
{
public:
	TileWaypointVO(ITile* source_, int targetRow_, int targetColumn_);

	ITile* source;
	int targetRow;
	int targetColumn;

	virtual ~TileWaypointVO();
};

