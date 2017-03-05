#pragma once
#include <match3-toolbox\TickAnimation.h>
#include "Actor.h"
#include <king\Engine.h>
class FloatingTextAnimation :
	public TickAnimation
{
public:
	FloatingTextAnimation(float x_, float y_, char* text, King::Engine* engine_);
	~FloatingTextAnimation();

	void start(float tick_);
	void update(float tick_);
	void end(float tick_);
private:
	float _x;
	float _y;
	char* _text;
	King::Engine* _engine;

	float _duration;
	float _speed;
};

