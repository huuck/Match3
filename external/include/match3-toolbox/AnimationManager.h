#pragma once
#include "TickAnimation.h"
#include <vector>

class AnimationManager
{
public:
	AnimationManager();

	void update(float tick_);
	void addAnimation(float tick_, TickAnimation* animation_);
	bool isIdle();

	~AnimationManager();

private:
	std::vector<TickAnimation*> _animations;
};

