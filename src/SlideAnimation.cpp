#include "SlideAnimation.h"
#include <math.h>
const float BASE_DURATION = 0.075f;
const float END_DURATION = 0.025f;
const float FPS = 60.0f;
SlideAnimation::SlideAnimation(Actor* targetActor_, int targetRow_, int targetColumn_) :	_speedX(0),
									_speedY(0){
	_targetActor = targetActor_;
	_targetRow = targetRow_;
	_targetColumn = targetColumn_;
}

SlideAnimation::~SlideAnimation() {
}

void SlideAnimation::start(float tick_) {
	TickAnimation::start(tick_);
	int columnDiff = _targetColumn - _targetActor->getColumn();
	int rowDiff = _targetRow - _targetActor->getRow();
	float diff = sqrt(columnDiff * columnDiff + rowDiff * rowDiff);
	_duration = diff * BASE_DURATION;
	_speedX = columnDiff * TILE_WIDTH / (_duration * FPS);
	_speedY = rowDiff * TILE_HEIGHT / (_duration * FPS);
}

void SlideAnimation::update(float tick_) {
	TickAnimation::update(tick_);

	if (currentState == STATE_RUNNING) {
		if (currentLocalTick <= _duration) {
			_targetActor->setViewX(_targetActor->getViewX() + _speedX);
			_targetActor->setViewY(_targetActor->getViewY() + _speedY);
		} else if (currentLocalTick < _duration + END_DURATION) {
			//add a bit of bounce at the end using a dampened cosine
			_targetActor->setViewX(_targetActor->getViewX() + _speedX * cos(50 * (currentLocalTick - _duration)) * exp(-(currentLocalTick - _duration)) * 0.15);
			_targetActor->setViewY(_targetActor->getViewY() + _speedY * cos(50 * (currentLocalTick - _duration)) * exp(-(currentLocalTick - _duration)) * 0.15);
		} else {
			SlideAnimation::end(tick_);
		}
	}
}

void SlideAnimation::end(float tick_) {
	TickAnimation::end(tick_);
	_targetActor->setViewX(_targetColumn * TILE_WIDTH);
	_targetActor->setViewY(_targetRow * TILE_HEIGHT);
}
