#include "IMatchRule.h"


IMatchRule::IMatchRule() {
}

std::vector<MatchVO*> IMatchRule::getMatches(IBoard* board_) {
	return std::vector<MatchVO*>();
}


IMatchRule::~IMatchRule() {
}
