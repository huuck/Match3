#pragma once
#include <king\Engine.h>
#include <match3-toolbox\StateMachine.h>
#include <match3-toolbox\AnimationManager.h>
#include <match3-toolbox\DefaultTile.h>

const int TILE_WIDTH = 45;
const int TILE_HEIGHT = 45;

class Actor
{
public:
	Actor(DefaultTile* tileData_);
	~Actor();

	King::Engine::Texture getViewID();
	float getViewX() { return _viewX; };
	float getViewY() { return _viewY; };

	void setViewX(float newX_);
	void setViewY(float newY_);

	int getRow() { return _tileData->getRow(); };
	int getColumn() { return _tileData->getColumn(); };

	ITile* getTileData() { return _tileData; };

	void setRow(int row_);
	void setColumn(int column_);

	int getCurrentStateID() { return _stateMachine.getCurrentStateID(); };


	void setViewScale(float scale_);
	void setViewRotation(float rotation_);
	float getViewRotation() { return _viewRotation; };
	float getViewScale() { return _viewScale; };

	void select();
	void reset();
	void destroy();
	void fall(int row_, int column_);
	bool isDestroyed();

	void update(float ticks_);

	void onStateIdleEnter(int previousState_);
	void onStateIdleUpdate();
	void onStateIdleExit(int nextState_);

	void onStateSelectedEnter(int previousState_);
	void onStateSelectedUpdate();
	void onStateSelectedExit(int nextState_);

	void onStateFallingEnter(int previousState_);
	void onStateFallingUpdate();
	void onStateFallingExit(int nextState_);

	void onStateDestroyedEnter(int previousState_);
	void onStateDestroyedUpdate();
	void onStateDestroyedExit(int nextState_);
private:
	float _currentTick;

	float _viewX;
	float _viewY;
	float _viewRotation;
	float _viewScale;

	DefaultTile* _tileData;

	StateMachine _stateMachine;
	AnimationManager _animationManager;
};

