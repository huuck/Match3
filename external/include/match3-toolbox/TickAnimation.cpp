#include "TickAnimation.h"


TickAnimation::TickAnimation() : currentGlobalTick(0), currentLocalTick(0), currentState(STATE_IDLE), startTick(0), endTick(0) {
}

bool TickAnimation::isDone() {
	return currentState == STATE_DONE;
}

void TickAnimation::start(float tick_) {
	startTick = tick_;
	currentGlobalTick = tick_;
	currentState = STATE_RUNNING;
}

void TickAnimation::update(float tick_) {
	currentGlobalTick = tick_;
	currentLocalTick = tick_ - startTick;
}

void TickAnimation::end(float tick_) {
	endTick = tick_;
	currentState = STATE_DONE;
}


TickAnimation::~TickAnimation() {
}
