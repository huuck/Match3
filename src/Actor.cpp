#include "Actor.h"
#include <math.h>

const int ACTOR_STATE_IDLE = 1;
const int ACTOR_STATE_SELECTED = 2;
const int ACTOR_STATE_FALLING = 3;
const int ACTOR_STATE_DESTROYED = 4;

Actor::Actor(DefaultTile* tileData_):	_stateMachine(false),
									_animationManager(),
									_currentTick(0),
									_viewRotation(0.0f),
									_viewScale(1.0f),
									_viewX(0),
									_viewY(0),
									_tileData(nullptr) {
	_tileData = tileData_;

	_stateMachine.addState(ACTOR_STATE_IDLE, std::vector<int> {ACTOR_STATE_IDLE, ACTOR_STATE_SELECTED, ACTOR_STATE_FALLING}, std::bind(&Actor::onStateIdleEnter, this, std::placeholders::_1), std::bind(&Actor::onStateIdleUpdate, this), std::bind(&Actor::onStateIdleExit, this, std::placeholders::_1));
	_stateMachine.addState(ACTOR_STATE_SELECTED, std::vector<int> {ACTOR_STATE_IDLE}, std::bind(&Actor::onStateSelectedEnter, this, std::placeholders::_1), std::bind(&Actor::onStateSelectedUpdate, this), std::bind(&Actor::onStateSelectedExit, this, std::placeholders::_1));
	_stateMachine.addState(ACTOR_STATE_FALLING, std::vector<int> {ACTOR_STATE_IDLE}, std::bind(&Actor::onStateFallingEnter, this, std::placeholders::_1), std::bind(&Actor::onStateFallingUpdate, this), std::bind(&Actor::onStateFallingExit, this, std::placeholders::_1));
	_stateMachine.addState(ACTOR_STATE_DESTROYED, std::vector<int> {ACTOR_STATE_IDLE, ACTOR_STATE_SELECTED, ACTOR_STATE_FALLING}, std::bind(&Actor::onStateDestroyedEnter, this, std::placeholders::_1), std::bind(&Actor::onStateDestroyedUpdate, this), std::bind(&Actor::onStateDestroyedExit, this, std::placeholders::_1));
	_stateMachine.setInitialState(ACTOR_STATE_IDLE);
}


Actor::~Actor() {
}

King::Engine::Texture Actor::getViewID() {
	King::Engine::Texture textureID = King::Engine::TEXTURE_MAX;

	switch (_tileData->getType()) {
		case 0: textureID = King::Engine::TEXTURE_BLUE; break;
		case 1: textureID = King::Engine::TEXTURE_GREEN; break;
		case 2: textureID = King::Engine::TEXTURE_PURPLE; break;
		case 3: textureID = King::Engine::TEXTURE_RED; break;
		case 4: textureID = King::Engine::TEXTURE_YELLOW; break;
		default: break;
	}

	return textureID;
}

void Actor::setViewX(float newX_) {
	_viewX = newX_;
}

void Actor::setViewY(float newY_) {
	_viewY = newY_;
}

void Actor::setRow(int row_) {
	_tileData->setRow(row_);
}

void Actor::setColumn(int column_) {
	_tileData->setColumn(column_);
}

void Actor::setViewScale(float scale_) {
	_viewScale = scale_;
}

void Actor::setViewRotation(float rotation_) {
	_viewRotation = rotation_;
}

void Actor::select() {
	_stateMachine.changeState(ACTOR_STATE_SELECTED);
}

void Actor::reset() {
	_stateMachine.changeState(ACTOR_STATE_IDLE);
}

void Actor::destroy() {
	_stateMachine.changeState(ACTOR_STATE_DESTROYED);
}

void Actor::fall(int row_, int column_) {
	_tileData->setRow(row_);
	_tileData->setColumn(column_);
	_stateMachine.changeState(ACTOR_STATE_FALLING);
}

bool Actor::isDestroyed() {
	return _stateMachine.getCurrentStateID() == ACTOR_STATE_DESTROYED;
}

void Actor::update(float ticks_) {
	_stateMachine.update();
	_currentTick += ticks_;
}

void Actor::onStateIdleEnter(int previousState_) {
}

void Actor::onStateIdleUpdate() {
	_viewX = _tileData->getColumn() * TILE_WIDTH;
	_viewY = _tileData->getRow() * TILE_HEIGHT;
}

void Actor::onStateIdleExit(int nextState_) {
}

void Actor::onStateSelectedEnter(int previousState_) {
	
}

void Actor::onStateSelectedUpdate() {
	_viewY += sin(_currentTick * 10.0f) * 0.1f;
}

void Actor::onStateSelectedExit(int nextState_) {
}

void Actor::onStateFallingEnter(int previousState_) {
}

void Actor::onStateFallingUpdate() {
}

void Actor::onStateFallingExit(int nextState_) {
}

void Actor::onStateDestroyedEnter(int previousState_) {
}

void Actor::onStateDestroyedUpdate() {
}

void Actor::onStateDestroyedExit(int nextState_) {
}
