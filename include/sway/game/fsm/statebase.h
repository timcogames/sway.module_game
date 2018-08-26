#ifndef SWAY_GAME_FSM_STATEBASE_H
#define SWAY_GAME_FSM_STATEBASE_H

#include <sway/game/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class IStateBase {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 */
	IStateBase() {
		// Empty
	}

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	virtual ~IStateBase() {
		// Empty
	}

	virtual void enter() = 0;

	virtual void exit() = 0;

	virtual void pause() = 0;

	virtual void resume() = 0;

	virtual void frameStarted(float timeStep) = 0;

	virtual void frameEnded() = 0;

	void setContext(core::foundation::Context * context) {
		_context = context;
	}

	core::foundation::Context * getContext() {
		return _context;
	}

private:
	core::foundation::Context * _context;
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_FSM_STATEBASE_H
