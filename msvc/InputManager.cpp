#include "InputManager.h"



InputManager::InputManager() : _isMouseButtonPressed(false) {
}


InputManager::~InputManager() {
}

InputManager::InputType InputManager::processButtonState(bool mouseButtonDown_) {
	if (_isMouseButtonPressed == false && mouseButtonDown_ == true) {
		return InputManager::InputType::INPUT_MOUSE_DOWN;
	} else if (_isMouseButtonPressed == true && mouseButtonDown_ == true) {
		return InputManager::InputType::INPUT_MOUSE_MOVE;
	} else if (_isMouseButtonPressed == true && mouseButtonDown_ == false) {
		return InputManager::InputType::INPUT_MOUSE_UP;
	}
}

void InputManager::selectTile(MockTile* selectedTile_) {
}

void InputManager::selectOtherTile(MockBoard* otherTile_) {
}
