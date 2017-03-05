#pragma once
#include <unordered_map>
#include "State.h"

class StateMachine
{
public:
	StateMachine(bool verbose_);

	void addState(int name_, std::vector<int> from_, std::function<void(int)> enter_, std::function<void()> update_, std::function<void(int)> exit_);
	void update();
	void changeState(int newState_);
	void setInitialState(int initialState_);

	int getCurrentStateID() { return _currentStateID; }
	int getLastStateID() { return _lastStateID; }

	~StateMachine();

private:
	bool _verbose = false;

	bool canChangeTo(int newState_);

	State* _currentState;
	int _currentStateID;
	int _lastStateID;
	std::unordered_map<int, State*> _states;
};

