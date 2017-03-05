#include "FloatingTextAnimation.h"
const float BASE_DURATION = 0.5f;
const float FPS = 60.0f;
FloatingTextAnimation::FloatingTextAnimation(float x_, float y_, char* text_, King::Engine* engine_) : _speed(0) {
	_x = x_;
	_y = y_;
	_text = text_;
	_engine = engine_;
}

FloatingTextAnimation::~FloatingTextAnimation() {
}

void FloatingTextAnimation::start(float tick_) {
	TickAnimation::start(tick_);
	_speed = 50.0f / (BASE_DURATION * FPS);
}

void FloatingTextAnimation::update(float tick_) {
	TickAnimation::update(tick_);
	float x;
	float scale;
	if (currentState == STATE_RUNNING) {
		if (currentLocalTick <= BASE_DURATION) { 
			//sets the scale based on a quadratic function and caps it at 1
			x = currentLocalTick / BASE_DURATION;
			scale = (-x * x + x) * 6;
			scale = scale > 1 ? 1 : scale;

			_engine->Write(_text, _x, _y, 0.0f, scale);
			_y -= _speed;
		} else {
			FloatingTextAnimation::end(tick_);
		}
	}
}

void FloatingTextAnimation::end(float tick_) {
	TickAnimation::end(tick_);

	delete _text;
}
