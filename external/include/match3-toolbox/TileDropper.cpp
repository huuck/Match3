#include "TileDropper.h"


TileDropper::TileDropper(IBoard* board_) {
	_board = board_;
	setupRules();
}

std::vector<TileWaypointVO*> TileDropper::dropTiles() {
	std::vector<TileWaypointVO*> ret;

	int i;
	for (i = 0; i < _rules.size(); i++) {
		std::vector<TileWaypointVO*> droppedTiles = _rules[i]->applyTo(_board);
		ret.insert(ret.begin(), droppedTiles.begin(), droppedTiles.end());
	}

	return ret;
}

bool TileDropper::isBoardStable() {
	int i;

	for (i = 0; i < _rules.size(); i++) {
		if (!_rules[i]->isBoardStable(_board)) {
			return false;
		}
	}

	return true;
}



TileDropper::~TileDropper() {
}
