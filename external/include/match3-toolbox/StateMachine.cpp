#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine(bool verbose_) {
	_verbose = verbose_;
}

void StateMachine::addState(int name_, std::vector<int> from_, std::function<void(int)> enter_, std::function<void()> update_, std::function<void(int)> exit_) {
	if (_states.find(name_) == _states.end())
	{
		State* state = new State(name_, from_, enter_, update_, exit_);
		_states[name_] = state;
	}
	else if(_verbose == true)
		printf("Tried to add an already existing state!\n");
}

void StateMachine::update() {
	_currentState->update();
}

void StateMachine::changeState(int newStateID_) {
	if (_states.find(newStateID_) == _states.end()) {
		if (_verbose) {
			printf("State %d does not exist!\n", _currentStateID);
		}
		return;
	}
		

	if (!canChangeTo(newStateID_)) {
		if (_verbose) {
			printf("Cannot change from state %d to %d!\n", _currentStateID, newStateID_);
		}
		return;
	} else {
		_currentState->exit(newStateID_);
		if (_verbose) {
			printf("State changed from %d to %d!\n", _currentStateID, newStateID_);
		}

		_lastStateID = _currentStateID;
		_currentStateID = newStateID_;
		
		_currentState = _states[newStateID_];
		_currentState->enter(_lastStateID);
	}
}

void StateMachine::setInitialState(int initialState_) {
	if (_states.find(initialState_) == _states.end()) {
		if (_verbose) {
			printf("State %d does not exist!\n", _currentStateID);
		}
		return;
	}

	_currentStateID = initialState_;
	_currentState = _states[initialState_];
	_currentState->enter(-1);

	if (_verbose) {
		printf("Set initial state to %d\n", initialState_);
	}
}



StateMachine::~StateMachine() {
}

bool StateMachine::canChangeTo(int newStateID_) {
	if (_states.find(newStateID_) == _states.end()) {
		printf("Could not find state with id %d!\n", newStateID_);
	}
	State* newState = _states[newStateID_];

	return std::find(newState->from.begin(), newState->from.end(), _currentStateID) != newState->from.end();
}
