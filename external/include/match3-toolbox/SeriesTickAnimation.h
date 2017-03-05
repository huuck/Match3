#pragma once
#include "TickAnimation.h"
#include <vector>
class SeriesTickAnimation :
	public TickAnimation
{
public:
	SeriesTickAnimation();

	void addAnimation(TickAnimation* newAnimation_);
	bool isDone();
	void start(float tick_);
	void update(float tick_);
	void end(float tick_);

	~SeriesTickAnimation();

private:
	std::vector<TickAnimation*> _animationQueue;
};

