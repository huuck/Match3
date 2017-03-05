#pragma once

const int STATE_IDLE = 1;
const int STATE_RUNNING = 2;
const int STATE_DONE = 3;

class TickAnimation
{
public:
	TickAnimation();

	bool isDone();
	virtual void start(float tick_);
	virtual void update(float tick_);
	virtual void end(float tick_);

	~TickAnimation();

protected:
	int currentState;
	float currentGlobalTick;
	float currentLocalTick;

	float startTick;
	float endTick;

};

