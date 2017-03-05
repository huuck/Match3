#include "Game.h"
#include "SlideAnimation.h"
#include "DestructionAnimation.h"
#include "FloatingTextAnimation.h"
#include <match3-toolbox\MatchVO.h>

const int GAME_DURATION = 60;
const int BOARD_START_X = 320;
const int BOARD_START_Y = 100;

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;
const int NUM_TILES = 5;
const int SCORE_PER_TILE = 50;

const int GAME_STATE_PREGAME = 1;
const int GAME_STATE_IDLE = 2;
const int GAME_STATE_INPUT = 3;
const int GAME_STATE_ANIMATING = 4;
const int GAME_STATE_MATCHING = 5;
const int GAME_STATE_DROPPING = 6;
const int GAME_STATE_POSTGAME = 7;

Game::Game() :	_mEngine("./assets"),
				_board(BOARD_WIDTH, BOARD_HEIGHT),
				_stateMachine(true),
				_inputManager(),
				_animationManager(),
				_stateBeforeAnimation(0),
				_ticks(0.0f),
				_startTick(0),
				_score(0),
				_cascadeMultiplier(1),
				_matcher(&_board),
				_dropper(&_board) {

	_stateMachine.addState(GAME_STATE_PREGAME, std::vector<int> {GAME_STATE_POSTGAME}, std::bind(&Game::onStatePregameEnter, this, std::placeholders::_1), std::bind(&Game::onStatePregameUpdate, this), std::bind(&Game::onStatePregameExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_IDLE, std::vector<int> {GAME_STATE_IDLE, GAME_STATE_INPUT, GAME_STATE_ANIMATING, GAME_STATE_MATCHING, GAME_STATE_DROPPING}, std::bind(&Game::onStateIdleEnter, this, std::placeholders::_1), std::bind(&Game::onStateIdleUpdate, this), std::bind(&Game::onStateIdleExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_INPUT, std::vector<int> {GAME_STATE_IDLE}, std::bind(&Game::onStateInputEnter, this, std::placeholders::_1), std::bind(&Game::onStateInputUpdate, this), std::bind(&Game::onStateInputExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_ANIMATING, std::vector<int> {GAME_STATE_INPUT, GAME_STATE_MATCHING, GAME_STATE_DROPPING}, std::bind(&Game::onStateAnimatingEnter, this, std::placeholders::_1), std::bind(&Game::onStateAnimatingUpdate, this), std::bind(&Game::onStateAnimatingExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_MATCHING, std::vector<int> {GAME_STATE_INPUT, GAME_STATE_ANIMATING, GAME_STATE_DROPPING}, std::bind(&Game::onStateMatchingEnter, this, std::placeholders::_1), std::bind(&Game::onStateMatchingUpdate, this), std::bind(&Game::onStateMatchingExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_DROPPING, std::vector<int> {GAME_STATE_ANIMATING, GAME_STATE_PREGAME}, std::bind(&Game::onStateDroppingEnter, this, std::placeholders::_1), std::bind(&Game::onStateDroppingUpdate, this), std::bind(&Game::onStateDroppingExit, this, std::placeholders::_1));
	_stateMachine.addState(GAME_STATE_POSTGAME, std::vector<int> {GAME_STATE_IDLE}, std::bind(&Game::onStatePostgameEnter, this, std::placeholders::_1), std::bind(&Game::onStatePostgameUpdate, this), std::bind(&Game::onStatePostgameExit, this, std::placeholders::_1));

	_stateMachine.setInitialState(GAME_STATE_PREGAME);
}
void Game::Start() {
	_mEngine.Start(*this);
}

void Game::Update() {
	renderGame();
	
	_ticks += _mEngine.GetLastFrameSeconds();
	_stateMachine.update();
	updateActors(_mEngine.GetLastFrameSeconds());
	_animationManager.update(_ticks);

	renderUI();
}

void Game::updateActors(float ticks_) {
	int i;

	for (i = 0; i < _actors.size(); i++) {
		_actors[i]->update(ticks_);
	}
}

void Game::init() {
}

Game::~Game() {
}

void Game::onStatePregameEnter(int previousState_) {
}

void Game::onStatePregameUpdate() {
	renderPreGame();
	if (_mEngine.GetMouseButtonDown()) {
		_stateMachine.changeState(GAME_STATE_DROPPING);
	}
}

void Game::onStatePregameExit(int nextState_) {
	int i, j;

	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			addTile(j, i, rand() % NUM_TILES);
		}
	}

	//clean  the board for any matches
	std::vector<MatchVO*> matches;
	do {
		matches = _matcher.getMatches();

		for (i = 0; i < matches.size(); i++) {
			for (j = 0; j < matches[i]->getSize(); j++) {
				matches[i]->getGroup()[j]->setType(rand() % NUM_TILES);
			}
		}
	} while (matches.size() > 0);

	_board.printBoard();

	_board.shiftBoardVertically(-BOARD_HEIGHT);

	updateActors(0);

	_cascadeMultiplier = 1;
	_score = 0;
	_startTick = _ticks;
}

void Game::onStateIdleEnter(int previousState_) {
	int i;
	for (i = 0; i < _actors.size(); i++) {
		_actors[i]->reset();
		_cascadeMultiplier = 1;
	}
}

void Game::onStateIdleUpdate() {
	if (_mEngine.GetMouseButtonDown()) {
		_stateMachine.changeState(GAME_STATE_INPUT);
	} else {
		if (_ticks - _startTick > GAME_DURATION) {
			_stateMachine.changeState(GAME_STATE_POSTGAME);
		}
	}
}

void Game::onStateIdleExit(int nextState_) {
}

void Game::onStateInputEnter(int previousState_) {
}

void Game::onStateInputUpdate() {
	int selectedRow = (_mEngine.GetMouseY() - BOARD_START_Y) / TILE_HEIGHT;
	int selectedColumn = (_mEngine.GetMouseX() - BOARD_START_X) / TILE_WIDTH;

	Actor* selectedActor = getActor(selectedColumn, selectedRow);
	InputManager::InputType input = _inputManager.processButtonState(_mEngine.GetMouseButtonDown());

	if (selectedActor != nullptr) {
		if (input == InputManager::InputType::INPUT_MOUSE_DOWN) {
			_inputManager.selectActor(selectedActor);
			selectedActor->select();
		}
		else if (input == InputManager::InputType::INPUT_MOUSE_UP) {
			_inputManager.selectOtherActor(selectedActor);
			selectedActor->select();
		}
	}

	if (_inputManager.isInputComplete()) {
		if (_inputManager.isSwapValid()) {
			//swaps the two tiles together
			_animationManager.addAnimation(_ticks, new SlideAnimation(_inputManager.getSelectedActor(), _inputManager.getOtherActor()->getRow(), _inputManager.getOtherActor()->getColumn()));
			_animationManager.addAnimation(_ticks, new SlideAnimation(_inputManager.getOtherActor(), _inputManager.getSelectedActor()->getRow(), _inputManager.getSelectedActor()->getColumn()));
			_inputManager.swap();
			_stateMachine.changeState(GAME_STATE_ANIMATING);
		} else {
			_inputManager.resetSelectedActors();
			_stateMachine.changeState(GAME_STATE_IDLE);
		}
		
	}
}

void Game::onStateInputExit(int nextState_) {
}

void Game::onStateAnimatingEnter(int previousState_) {
	_stateBeforeAnimation = previousState_;
}

void Game::onStateAnimatingUpdate() {
	if (_animationManager.isIdle()) {
		switch (_stateBeforeAnimation) {
			case GAME_STATE_INPUT: _stateMachine.changeState(GAME_STATE_MATCHING); break;
			case GAME_STATE_MATCHING: {
				//did we get here after an incorrect switch?
				if (_inputManager.isInputComplete()) {
					_inputManager.resetSelectedActors();
					_stateMachine.changeState(GAME_STATE_IDLE);
				} else {
					_stateMachine.changeState(GAME_STATE_DROPPING);
				}
			}; break;
			case GAME_STATE_DROPPING: {
				_stateMachine.changeState(GAME_STATE_DROPPING);
			}; break;
		}
	}
}

void Game::onStateAnimatingExit(int nextState_) {
	//clean up any destroyed tiles/actors
	int i, j;
	Actor* destroyedActor;
	ITile* destroyedTile;

	for (i = 0; i < _actors.size(); i++) {
		if (_actors[i]->isDestroyed()) {
			destroyedActor = _actors[i];
			destroyedTile = destroyedActor->getTileData();
			removeActor(destroyedActor);
			_board.remove(destroyedTile);
			i--;
		}
	}
}

void Game::onStateMatchingEnter(int previousState_) {
	int i, j;
	std::vector<MatchVO*> matches = _matcher.getMatches();
	_board.printBoard();
	if (matches.size() == 0) {
		//did we get here after an incorrect match?
		if (_inputManager.isInputComplete()) {
			_animationManager.addAnimation(_ticks, new SlideAnimation(_inputManager.getSelectedActor(), _inputManager.getOtherActor()->getRow(), _inputManager.getOtherActor()->getColumn()));
			_animationManager.addAnimation(_ticks, new SlideAnimation(_inputManager.getOtherActor(), _inputManager.getSelectedActor()->getRow(), _inputManager.getSelectedActor()->getColumn()));
			_inputManager.swap();
			_stateMachine.changeState(GAME_STATE_ANIMATING);
		//or after tiles have dropped and we don't have any more matches?
		} else {
			_stateMachine.changeState(GAME_STATE_IDLE);
		}		
	} else {
		Actor* matchedActor;
		int score;
		//did we get here after a switch?
		if (_inputManager.isInputComplete()) {
			_inputManager.getSelectedActor()->reset();
			_inputManager.getOtherActor()->reset();
			_inputManager.resetSelectedActors();
		}
		
		int k;
		int averageX = 0, averageY = 0;
		int totalScore = 0;
		for (i = 0; i < matches.size(); i++) {
			averageX = 0;
			averageY = 0;
			totalScore = 0;
			for (j = 0; j < matches[i]->getSize(); j++) {
				matchedActor = getActor(matches[i]->getGroup()[j]->getColumn(), matches[i]->getGroup()[j]->getRow());
				averageX += matchedActor->getViewX();
				averageY += matchedActor->getViewY();
				if (!matchedActor->isDestroyed()) {
					//destroyed the matched tile
					_animationManager.addAnimation(_ticks, new DestructionAnimation(matchedActor));
					score = SCORE_PER_TILE * _cascadeMultiplier * (matches[i]->getSize() - 2);
					_score += score;
					totalScore += score;
					matchedActor->destroy();
				}
			}

			//add floating text
			averageX /= matches[i]->getSize();
			averageY /= matches[i]->getSize();

			char* buff = new char[32];
			sprintf_s(buff, 32, "+%d", totalScore);
			_animationManager.addAnimation(_ticks, new FloatingTextAnimation(BOARD_START_X + averageX, BOARD_START_Y + averageY, buff, &_mEngine));
		}

		_cascadeMultiplier++;
		_stateMachine.changeState(GAME_STATE_ANIMATING);
	}

	//clean up the match containers
	for (i = 0; i < matches.size(); i++) {
		delete matches[i];
	}
}

void Game::onStateMatchingUpdate() {
}

void Game::onStateMatchingExit(int nextState_) {
	int i, j;
	//add any missing tiles
	//fill any board holes by adding more tiles on top
	Actor* actor;
	for (i = 0; i < _board.getNumRows(); i++) {
		for (j = 0; j < _board.getNumColumns(); j++) {
			actor = getActor(j, i);
			if (actor->isDestroyed()) {
				addTile(j, i - _board.getNumRows(), rand() % NUM_TILES);
			}
		}
	}
}

void Game::onStateDroppingEnter(int previousState_) {
	int i;
	Actor* actor;
	//checks if the board is stable
	if (!_dropper.isBoardStable()) {
		//drops the tiles on the ground (doesn't drop them all the way, just step at a time)
		std::vector<TileWaypointVO*> waypoints = _dropper.dropTiles();
		for (i = 0; i < waypoints.size(); i++) {
			actor = getActor(waypoints[i]->source->getColumn(), waypoints[i]->source->getRow());
			_animationManager.addAnimation(_ticks, new SlideAnimation(actor, waypoints[i]->targetRow, waypoints[i]->targetColumn));
			actor->fall(waypoints[i]->targetRow, waypoints[i]->targetColumn);
		}

		for (i = 0; i < waypoints.size(); i++) {
			delete waypoints[i];
		}

		_stateMachine.changeState(GAME_STATE_ANIMATING);
	} else {
		//board looks allright, let's see if we have any cascading matches
		if (_matcher.getMatches().size() > 0) {
			_stateMachine.changeState(GAME_STATE_MATCHING);
		} else {
			_stateMachine.changeState(GAME_STATE_IDLE);
		}
	}
}

void Game::onStateDroppingUpdate() {
}

void Game::onStateDroppingExit(int nextState_) {
	
}

void Game::onStatePostgameEnter(int previousState_) {
	int i;

	for (i = 0; i < _actors.size(); i++) {
		_animationManager.addAnimation(_ticks, new SlideAnimation(_actors[i], _actors[i]->getRow() - BOARD_HEIGHT * 2, _actors[i]->getColumn()));
		_board.shiftBoardVertically(-BOARD_HEIGHT * 2);
		_actors[i]->destroy();
	}
}

void Game::onStatePostgameUpdate() {
	if (_mEngine.GetMouseButtonDown() && _animationManager.isIdle()) {
		_stateMachine.changeState(GAME_STATE_PREGAME);
	}

	if (_animationManager.isIdle()) {
		renderPostGame();
	}
}

void Game::onStatePostgameExit(int nextState_) {
	int i;
	Actor* destroyedActor;
	ITile* destroyedTile;
	for (i = 0; i < _actors.size(); i++) {
		destroyedActor = _actors[i];
		destroyedTile = destroyedActor->getTileData();
		removeActor(destroyedActor);
		_board.remove(destroyedTile);
		i--;
	}
}

void Game::addTile(int column_, int row_, int type_) {
	 DefaultTile* newTile = _board.addTile(row_, column_, type_);
	 Actor* newActor = new Actor(newTile);
	 newActor->update(_ticks);
	_actors.push_back(newActor);
}

Actor* Game::getActor(int column_, int row_) {
	int i;
	for (i = 0; i < _actors.size(); i++)
	{
		if (_actors[i]->getRow() == row_ && _actors[i]->getColumn() == column_)
		{
			return _actors[i];
		}
	}
	return nullptr;
}

void Game::removeActor(Actor* actor_) {
	auto iterator = std::find(_actors.begin(), _actors.end(), actor_);

	if (iterator != _actors.end()) {
		_actors.erase(iterator);
		delete actor_;
	}
}

void Game::renderPreGame() {
	_mEngine.Write("Welcome!", 430, 200);
	_mEngine.Write("Press <LMP> to start!", 350, 300);
}

void Game::renderGame() {
	_mEngine.Render(King::Engine::TEXTURE_DARKNESS, 300.0f, 90.0f);

	int i;
	for (i = 0; i < _actors.size(); i++) {
		_mEngine.Render(_actors[i]->getViewID(), BOARD_START_X + _actors[i]->getViewX(), BOARD_START_Y + _actors[i]->getViewY(), _actors[i]->getViewRotation(), _actors[i]->getViewScale());
	}

	_mEngine.Render(King::Engine::TEXTURE_MINE, 0.0f, 0.0f);
}

void Game::renderUI() {
	if (_stateMachine.getCurrentStateID() != GAME_STATE_PREGAME && _stateMachine.getCurrentStateID() != GAME_STATE_POSTGAME) {
		_mEngine.Write("Score:", 100, 50);

		sprintf_s(buff, "%06d", _score);

		_mEngine.Write(buff, 100, 75);
		_mEngine.Write("Time left:", 100, 125);

		int minutes = (GAME_DURATION - (_ticks - _startTick)) / 60;
		int seconds = (GAME_DURATION - (int)(_ticks - _startTick)) % 60;

		minutes = minutes > 0 ? minutes : 0;
		seconds = seconds > 0 ? seconds : 0;

		sprintf_s(buff, "%02d:%02d", minutes, seconds);

		_mEngine.Write(buff, 100, 150);
	}
}

void Game::renderPostGame() {
	_mEngine.Write("Game Over", 430, 150);

	_mEngine.Write("Total Score:", 350, 250);
	sprintf_s(buff, "%d points", _score);

	_mEngine.Write(buff, 400, 300);

	_mEngine.Write("Press <LMP> to restart!", 350, 400);
}
