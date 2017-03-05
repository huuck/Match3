#include "TileMatcher.h"


TileMatcher::TileMatcher(IBoard* board_) {
	_board = board_;
	setupRules();
}

std::vector<MatchVO*> TileMatcher::getMatches() {
	std::vector<MatchVO*> ret;

	int i;

	for (i = 0; i < _rules.size(); i++) {
		std::vector<MatchVO*> matches = _rules[i]->getMatches(_board);
		ret.insert(ret.begin(), matches.begin(), matches.end());
	}

	return ret;
}

TileMatcher::~TileMatcher() {
}
