#pragma once
#include "TileMatcher.h"
class DefaultMatcher :
	public TileMatcher
{
public:
	DefaultMatcher(IBoard* board_);

	~DefaultMatcher();
};

