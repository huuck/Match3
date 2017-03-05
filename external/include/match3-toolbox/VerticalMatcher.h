#pragma once
#include "IMatchRule.h"
class VerticalMatcher :
	public IMatchRule
{
public:
	VerticalMatcher();
	std::vector<MatchVO*> getMatches(IBoard* board_);
	~VerticalMatcher();
};

