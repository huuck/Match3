#include "DefaultMatcher.h"
#include "HorizontalMatcher.h"
#include "VerticalMatcher.h"

DefaultMatcher::DefaultMatcher(IBoard* board) : TileMatcher(board) {

}

void TileMatcher::setupRules() {
	_rules.push_back(new HorizontalMatcher());
	_rules.push_back(new VerticalMatcher());
}


DefaultMatcher::~DefaultMatcher() {
}
