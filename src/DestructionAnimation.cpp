#include "DestructionAnimation.h"
const float BASE_DURATION = 0.5f;
const float FPS = 60.0f;
DestructionAnimation::DestructionAnimation(Actor* targetActor_) : _speed(0) {
	_targetActor = targetActor_;
}

DestructionAnimation::~DestructionAnimation() {
}

void DestructionAnimation::start(float tick_) {
	TickAnimation::start(tick_);
	_speed = 1 / (BASE_DURATION * FPS);
}

void DestructionAnimation::update(float tick_) {
	TickAnimation::update(tick_);

	if (currentState == STATE_RUNNING) {
		if (currentLocalTick <= BASE_DURATION) {
			_targetActor->setViewRotation(_targetActor->getViewRotation() + 0.5f);
			_targetActor->setViewScale(_targetActor->getViewScale() - _speed);
		} else {
			DestructionAnimation::end(tick_);
		}
	}
}

void DestructionAnimation::end(float tick_) {
	TickAnimation::end(tick_);
}
