#pragma once
#include <vector>
#include "IMatchRule.h"
#include "MatchVO.h"

class TileMatcher
{
public:
	TileMatcher(IBoard* board_);

	std::vector<MatchVO*> getMatches();

	~TileMatcher();

protected:
	std::vector<IMatchRule*> _rules;
	virtual void setupRules();

private:
	IBoard* _board;
};

