#pragma once
#include <vector>

#include <king/Engine.h>
#include <king/Updater.h>
#include "Actor.h"
#include "InputManager.h"
#include <match3-toolbox\DefaultBoard.h>
#include <match3-toolbox\DefaultMatcher.h>
#include <match3-toolbox\DefaultDropper.h>
class Game : King::Updater {
public:
	Game();
	void Start();
	void Update();
	void updateActors(float ticks_);
	void init();

	~Game();

private:
	King::Engine _mEngine;

	StateMachine _stateMachine;
	std::vector<Actor*> _actors;
	InputManager _inputManager;
	AnimationManager _animationManager;
	DefaultMatcher _matcher;
	DefaultDropper _dropper;
	float _ticks;
	float _startTick;
	int _score;
	int _cascadeMultiplier;
	DefaultBoard _board;
	//********************************************************
	//enter/update/exit state handlers for each state
	void onStatePregameEnter(int previousState_);
	void onStatePregameUpdate();
	void onStatePregameExit(int nextState_);

	void onStateIdleEnter(int previousState_);
	void onStateIdleUpdate();
	void onStateIdleExit(int nextState_);
	//entered when the user clicks a button
	void onStateInputEnter(int previousState_);
	void onStateInputUpdate();
	void onStateInputExit(int nextState_);
	//routes around states that have animations
	void onStateAnimatingEnter(int previousState_);
	void onStateAnimatingUpdate();
	void onStateAnimatingExit(int nextState_);
	//gets and processes matches, and then enters the animation state after adding the tiles that have been destroyed
	void onStateMatchingEnter(int previousState_);
	void onStateMatchingUpdate();
	void onStateMatchingExit(int nextState_);
	//drops tiles on the ground
	void onStateDroppingEnter(int previousState_);
	void onStateDroppingUpdate();
	void onStateDroppingExit(int nextState_);
	//score
	void onStatePostgameEnter(int previousState_);
	void onStatePostgameUpdate();
	void onStatePostgameExit(int nextState_);

	void addTile(int column_, int row_, int type_);
	int _stateBeforeAnimation;
	Actor* getActor(int column_, int row_);

	char buff[64];

	void removeActor(Actor* actor_);
	void renderPreGame();
	void renderGame();
	void renderUI();
	void renderPostGame();
};

