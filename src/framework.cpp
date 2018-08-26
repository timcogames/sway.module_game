#include <sway/game/framework.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Framework::Framework() {
	// Empty
}

Framework::~Framework() {
	// Empty
}

void Framework::startup(fsm::IStateBase * state) {
	_stateMgr = boost::make_shared<fsm::StateManager>();
	_stateMgr->changeState(state, this);
}

NAMESPACE_END(game)
NAMESPACE_END(sway)
