#include <sway/game/fsm/statemanager.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

StateManager::StateManager() {
	// Empty
}

StateManager::~StateManager() {
	while (!_stateStack.empty()) {
		_stateStack.back()->exit();
		_stateStack.pop_back();
	}
}

void StateManager::frameStarted(float timeStep) {
	_stateStack.back()->frameStarted(timeStep);
}

void StateManager::frameEnded() {
	_stateStack.back()->frameEnded();
}

void StateManager::changeState(AStateBase * state, core::foundation::Context * context) {
	while (!_stateStack.empty()) {
		_stateStack.back()->exit();
		_stateStack.pop_back();
	}

	_stateStack.push_back(state);
	_stateStack.back()->setContext(context);
	_stateStack.back()->enter();
}

void StateManager::pushState(AStateBase * state, core::foundation::Context * context) {
	if (!_stateStack.empty())
		_stateStack.back()->pause();

	_stateStack.push_back(state);
	_stateStack.back()->setContext(context);
	_stateStack.back()->enter();
}

void StateManager::popState() {
	while (!_stateStack.empty()) {
		_stateStack.back()->exit();
		_stateStack.pop_back();
	}

	if (!_stateStack.empty())
		_stateStack.back()->resume();
}

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)
