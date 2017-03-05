#pragma once
class ITile
{
public:
	ITile();

	virtual int getRow() = 0;
	virtual int getColumn() = 0;

	virtual void setColumn(int column_) = 0;
	virtual void setRow(int row_) = 0;

	virtual int getType() = 0;
	virtual void setType(int type_) = 0;

	virtual ~ITile();
};

