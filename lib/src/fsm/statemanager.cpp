#include <sway/game/fsm/statemanager.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

StateManager::StateManager() {
  // Empty
}

StateManager::~StateManager() {
  while (!stateStack_.empty()) {
    stateStack_.back()->exit();
    stateStack_.pop_back();
  }
}

void StateManager::frameStarted(float timeStep) { stateStack_.back()->frameStarted(timeStep); }

void StateManager::frameEnded() { stateStack_.back()->frameEnded(); }

void StateManager::changeState(StateBase *state, core::foundation::Context *context) {
  while (!stateStack_.empty()) {
    stateStack_.back()->exit();
    stateStack_.pop_back();
  }

  stateStack_.push_back(state);
  stateStack_.back()->setContext(context);
  stateStack_.back()->enter();
}

void StateManager::pushState(StateBase *state, core::foundation::Context *context) {
  if (!stateStack_.empty()) {
    stateStack_.back()->pause();
  }

  stateStack_.push_back(state);
  stateStack_.back()->setContext(context);
  stateStack_.back()->enter();
}

void StateManager::popState() {
  while (!stateStack_.empty()) {
    stateStack_.back()->exit();
    stateStack_.pop_back();
  }

  if (!stateStack_.empty()) {
    stateStack_.back()->resume();
  }
}

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)
