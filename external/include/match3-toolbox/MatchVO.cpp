#include "MatchVO.h"


MatchVO::MatchVO(std::vector<ITile*> group_) {
	_group = group_;
}

bool MatchVO::intersectsWith(MatchVO* match_) {
	int i, j;

	std::vector<ITile* > otherGroup = match_->getGroup();

	for (i = 0; i < _group.size(); i++) {
		for (j = 0; j < otherGroup.size(); j++) {
			if (_group[i] == otherGroup[j]) {
				return false;
			}
		}
	}
		

	return true;
}

void MatchVO::mergeWith(MatchVO* match_) {
	int i;

	std::vector<ITile* > otherGroup = match_->getGroup();

	for (i = 0; i < otherGroup.size(); i++) {
		if (!contains(otherGroup[i])) {
			_group.push_back(otherGroup[i]);
		}
	}
}


MatchVO::~MatchVO() {
}

bool MatchVO::contains(ITile* tile_) {
	int i;

	for (i = 0; i < _group.size(); i++) {
		if (_group[i] == tile_) {
			return true;
		}
	}

	return false;
}
