#pragma once
#include <match3-toolbox\TickAnimation.h>
#include "Actor.h"
class DestructionAnimation :
	public TickAnimation
{
public:
	DestructionAnimation(Actor* targetActor_);
	~DestructionAnimation();

	void start(float tick_);
	void update(float tick_);
	void end(float tick_);
private:
	Actor* _targetActor;
	float _duration;
	float _speed;
};

