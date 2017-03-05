#pragma once
#include "IMatchRule.h"
class HorizontalMatcher :
	public IMatchRule
{
public:
	HorizontalMatcher();
	std::vector<MatchVO*> getMatches(IBoard * board_);
	~HorizontalMatcher();
};

