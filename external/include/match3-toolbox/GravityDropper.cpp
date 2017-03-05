#include "GravityDropper.h"


GravityDropper::GravityDropper() {
}

std::vector<TileWaypointVO*> GravityDropper::applyTo(IBoard* board_) {
	std::vector<TileWaypointVO*> ret;
	std::vector<ITile*> droppingTiles;

	ITile* tile;
	TileWaypointVO* newWaypoint;
	int i, j, k; 

	for (j = 0; j < board_->getNumColumns(); j++) {
		for (i = board_->getNumRows() - 1; i >= -board_->getNumRows(); i--) {
			tile = board_->getTileAt(i, j);

			if (tile == nullptr) {
				newWaypoint = new TileWaypointVO(nullptr, i, j);

				k = i;

				do {
					tile = board_->getTileAt(k, j);
					k--;
					if (std::find(droppingTiles.begin(), droppingTiles.end(), tile) != droppingTiles.end()) {
						tile = nullptr;
					}
				} while (tile == nullptr && k >= -board_->getNumRows());

				if (tile != nullptr) {
					newWaypoint->source = tile;
					droppingTiles.push_back(tile);
					ret.push_back(newWaypoint);
				}
			}
		}
	}
		

	return ret;
}

bool GravityDropper::isBoardStable(IBoard* board) {
	int i, j;

	ITile* tile;
	bool foundBoardHole;

	for (j = 0; j < board->getNumColumns(); j++) {
		foundBoardHole = false;

		for (i = board->getNumRows() - 1; i >= -board->getNumRows(); i--) {
			tile = board->getTileAt(i, j);

			if (tile == nullptr) {
				foundBoardHole = true;
			} else if (foundBoardHole) {
				return false;
			}
		}
	}

	return true;
}


GravityDropper::~GravityDropper() {
}
