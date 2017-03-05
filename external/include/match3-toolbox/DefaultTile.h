#pragma once
#include "ITile.h"
class DefaultTile :
	public ITile
{
public:
	DefaultTile(int row_, int column_, int type_);
	int getRow();
	int getColumn();

	void setRow(int row_);
	void setColumn(int column_);

	int getType();
	void setType(int type_);
	~DefaultTile();

private:
	int _row;
	int _column;
	int _type;
};

