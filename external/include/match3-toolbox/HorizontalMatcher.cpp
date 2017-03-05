#include "HorizontalMatcher.h"


HorizontalMatcher::HorizontalMatcher() {
}

std::vector<MatchVO*> HorizontalMatcher::getMatches(IBoard* board) {
	int i, j, k;
	bool matchIsValid;
	std::vector<MatchVO*> ret;

	std::vector<ITile*> match;

	int maxHeight = board->getNumRows();
	int maxWidth = board->getNumColumns();

	//go by rows
	for (i = 0; i < maxHeight; i++) {
		for (j = 0; j < maxWidth; j += match.size()) {
			match.clear();
			match.insert(match.begin(), board->getTileAt(j, i));
			if (match[0] != nullptr) {
				matchIsValid = true;
				for (k = j + 1; k < maxWidth && matchIsValid; k++) {
					ITile* tile = board->getTileAt(k, i);

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

HorizontalMatcher::~HorizontalMatcher() {
}
