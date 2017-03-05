#include "VerticalMatcher.h"


VerticalMatcher::VerticalMatcher() {
}

std::vector<MatchVO*> VerticalMatcher::getMatches(IBoard* board_) {
	int i, j, k;
	bool matchIsValid;
	std::vector<MatchVO*> ret;

	std::vector<ITile*> match;

	int maxHeight = board_->getNumRows();
	int maxWidth = board_->getNumColumns();

	//go by rows
	for (i = 0; i < maxWidth; i++) {
		for (j = 0; j < maxHeight; j += match.size()) {
			match.clear();
			match.insert(match.begin(), board_->getTileAt(i, j));
			if (match[0] != nullptr) {
				matchIsValid = true;
				for (k = j + 1; k < maxWidth && matchIsValid; k++) {
					ITile* tile = board_->getTileAt(i, k);

					if (tile != nullptr) {
						if (match[0]->getType() == tile->getType()) {
							match.push_back(tile);
						} else {
							matchIsValid = false;
						}
					}
				}

				if (match.size() >= 3) {
					ret.push_back(new MatchVO(match));
				}
			}
		}
	}

	return ret;
}

VerticalMatcher::~VerticalMatcher() {
}
