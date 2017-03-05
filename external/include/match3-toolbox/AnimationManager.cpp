#include "AnimationManager.h"

AnimationManager::AnimationManager() {
}

void AnimationManager::update(float tick_) {
	int i;

	for (i = 0; i < _animations.size(); i++) {
		_animations[i]->update(tick_);

		if (_animations[i]->isDone()) {
			TickAnimation* finishedAnimation = _animations[i];
			_animations.erase(_animations.begin() + i);
			delete finishedAnimation;
			i--;
		}
	}
}

void AnimationManager::addAnimation(float tick, TickAnimation* animation) {
	_animations.push_back(animation);
	animation->start(tick);
}

bool AnimationManager::isIdle() {
	return _animations.size() == 0;
}


AnimationManager::~AnimationManager() {
}
