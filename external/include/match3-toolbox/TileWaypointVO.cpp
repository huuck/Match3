#include "TileWaypointVO.h"


TileWaypointVO::TileWaypointVO(ITile* source_, int targetRow_, int targetColumn_) {
	source = source_;
	targetRow = targetRow_;
	targetColumn = targetColumn_;
}


TileWaypointVO::~TileWaypointVO() {
}
