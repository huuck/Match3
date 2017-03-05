#pragma once
#include <vector>
#include "ITile.h"

class MatchVO
{
public:
	MatchVO(std::vector<ITile*> group_);

	bool intersectsWith(MatchVO* match_);
	void mergeWith(MatchVO* match_);

	std::vector<ITile*> getGroup() { return _group; }
	int getSize() { return _group.size(); }

	~MatchVO();

private:
	std::vector<ITile*> _group;

	bool contains(ITile* tile_);
};

