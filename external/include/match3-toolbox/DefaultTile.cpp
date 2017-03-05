#include "DefaultTile.h"


DefaultTile::DefaultTile(int row_, int column_, int type_) {
	_row = row_;
	_column = column_;
	_type = type_;
}

int DefaultTile::getRow() {
	return _row;
}

int DefaultTile::getColumn() {
	return _column;
}

void DefaultTile::setRow(int row_) {
	_row = row_;
}

void DefaultTile::setColumn(int column_) {
	_column = column_;
}

int DefaultTile::getType() {
	return _type;
}

void DefaultTile::setType(int type_) {
	_type = type_;
}

DefaultTile::~DefaultTile() {
}
