#include "DefaultBoard.h"
#include "DefaultTile.h"

const int STATE_IDLE = 1;

DefaultBoard::DefaultBoard(int width_, int height_ ) {
	_width = width_;
	_height = height_;
}

void DefaultBoard::printBoard() {
	int i, j;
	for (i = 0; i < _height; i++) {
		for (j = 0; j < _width; j++) {
			if (getTileAt(i, j) != nullptr) {
				printf("%d ", getTileAt(i, j)->getType());
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}

void DefaultBoard::remove(ITile* tile) {
	auto iterator = std::find(_tiles.begin(), _tiles.end(), tile);

	if (iterator != _tiles.end()) {
		_tiles.erase(iterator);
		delete tile;
	}
}

ITile* DefaultBoard::getTileAt(int row_, int column_) {
	int i;
	for (i = 0; i < _tiles.size(); i++) {
		if (_tiles[i]->getRow() == row_ && _tiles[i]->getColumn() == column_) {
			return _tiles[i];
		}
	}

	return nullptr;
}

void DefaultBoard::shiftBoardVertically(int numRows_) {
	int i;
	for (i = 0; i < _tiles.size(); i++) {
		_tiles[i]->setRow(_tiles[i]->getRow() + numRows_);
	}
}

DefaultBoard::~DefaultBoard() {
}

DefaultTile* DefaultBoard::addTile(int row_, int column_, int type_) {
	DefaultTile* newTile = new DefaultTile(row_, column_, type_);
	_tiles.push_back(newTile);

	return newTile;
}
