#pragma once
#include <match3-toolbox\TickAnimation.h>
#include "Actor.h"
class SlideAnimation :
	public TickAnimation
{
public:
	SlideAnimation(Actor* targetActor_, int targetRow_, int targetColumn_);
	~SlideAnimation();

	void start(float tick_);
	void update(float tick_);
	void end(float tick_);
private:
	Actor* _targetActor;
	int _targetRow;
	int _targetColumn;
	float _duration;
	float _speedX;
	float _speedY;
};

