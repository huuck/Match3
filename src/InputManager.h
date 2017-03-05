#pragma once
#include "Actor.h"
#include <match3-toolbox\DefaultTile.h>
class InputManager
{
public:
	enum InputType
	{
		INPUT_MOUSE_DOWN,
		INPUT_MOUSE_UP,
		INPUT_MOUSE_DRAG,
		INPUT_MOUSE_MOVE
	};
	InputManager();
	~InputManager();

	InputType processButtonState(bool mouseButtonDown_);
	void selectActor(Actor* selectedTile_);
	void selectOtherActor(Actor* otherTile_);

	Actor* getSelectedActor() { return _selectedActor; };
	Actor* getOtherActor() { return _otherActor; };

	void swap();

	bool isSwapValid();
	bool isInputComplete();

	void resetSelectedActors();
private:
	Actor* _selectedActor;
	Actor* _otherActor;

	bool _isMouseButtonPressed;
};

