#include "SeriesTickAnimation.h"


SeriesTickAnimation::SeriesTickAnimation():TickAnimation() {
}

void SeriesTickAnimation::addAnimation(TickAnimation* newAnimation_) {
	_animationQueue.push_back(newAnimation_);
}

bool SeriesTickAnimation::isDone() {
	return _animationQueue.size() == 0;
}

void SeriesTickAnimation::start(float tick_) {
	TickAnimation::start(tick_);

	if (_animationQueue.size() > 0) {
		_animationQueue[0]->start(tick_);
	}
}

void SeriesTickAnimation::update(float tick_) {
	TickAnimation::update(tick_);

	if (_animationQueue.size() > 0) {
		_animationQueue[0]->update(tick_);

		if (_animationQueue[0]->isDone() == true) {
			_animationQueue[0]->end(tick_);
			_animationQueue.erase(_animationQueue.begin());

			if (_animationQueue.size() > 0) {
				_animationQueue[0]->start(tick_);
			}
		}
	}
		
}

void SeriesTickAnimation::end(float tick_) {
}

SeriesTickAnimation::~SeriesTickAnimation() {
}
