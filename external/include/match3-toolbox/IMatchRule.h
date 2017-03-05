#pragma once
#include <vector>
#include "MatchVO.h"
#include "IBoard.h"

class IMatchRule
{
public:
	IMatchRule();

	virtual std::vector<MatchVO*> getMatches(IBoard* board_);

	~IMatchRule();
};

