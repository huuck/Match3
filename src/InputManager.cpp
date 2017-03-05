#include "InputManager.h"
#include <math.h>


InputManager::InputManager() :	_isMouseButtonPressed(false),
								_selectedActor(nullptr),
								_otherActor(nullptr) {
}


InputManager::~InputManager() {
}

//spits out the button state
InputManager::InputType InputManager::processButtonState(bool mouseButtonDown_) {
	InputManager::InputType newInput;

	if (_isMouseButtonPressed == false && mouseButtonDown_ == true) {
		newInput = InputManager::InputType::INPUT_MOUSE_DOWN;
	} else if (_isMouseButtonPressed == true && mouseButtonDown_ == true) {
		newInput = InputManager::InputType::INPUT_MOUSE_DRAG;
	} else if (_isMouseButtonPressed == true && mouseButtonDown_ == false) {
		newInput = InputManager::InputType::INPUT_MOUSE_UP;
	} else {
		newInput = InputManager::InputType::INPUT_MOUSE_MOVE;
	}

	_isMouseButtonPressed = mouseButtonDown_;

	return newInput;
}

void InputManager::selectActor(Actor* selectedActor_) {
	if (_selectedActor == nullptr) {
		_selectedActor = selectedActor_;
	}
}

void InputManager::selectOtherActor(Actor* otherActor_) {
	_otherActor = otherActor_;
}


void InputManager::swap() {
	int temp;
	temp = _selectedActor->getRow();
	_selectedActor->setRow(_otherActor->getRow());
	_otherActor->setRow(temp);

	temp = _selectedActor->getColumn();
	_selectedActor->setColumn(_otherActor->getColumn());
	_otherActor->setColumn(temp);
}

//checks if the swap is possible with the currently selected actors
bool InputManager::isSwapValid() {
	if (!isInputComplete()) {
		return false;
	}

	int rowDist = _selectedActor->getRow() - _otherActor->getRow();
	int columnDist = _selectedActor->getColumn() - _otherActor->getColumn();
	float dist = sqrt(rowDist * rowDist + columnDist * columnDist);
	if (dist > 0.99f && dist < 1.01f) {
		return true;
	} else {
		return false;
	}
}

//do we have a complet set of inputs?
bool InputManager::isInputComplete() {
	return _selectedActor != nullptr && _otherActor != nullptr && _selectedActor != _otherActor;
}

void InputManager::resetSelectedActors() {
	if(_selectedActor != nullptr)
		_selectedActor->reset();

	if (_otherActor != nullptr)
		_otherActor->reset();

	_selectedActor = nullptr;
	_otherActor = nullptr;
}
