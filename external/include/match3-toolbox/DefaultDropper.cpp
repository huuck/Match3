#include "DefaultDropper.h"
#include "GravityDropper.h"

DefaultDropper::DefaultDropper(IBoard* board_) : TileDropper(board_) {
}

void TileDropper::setupRules() {
	_rules.push_back(new GravityDropper());
}

DefaultDropper::~DefaultDropper() {
}
