#ifndef SWAY_GAME_FSM_STATEMANAGER_H
#define SWAY_GAME_FSM_STATEMANAGER_H

#include <sway/game/fsm/statebase.h>
#include <sway/game/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class StateManager {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	StateManager();

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~StateManager();

	/*!
	 * \brief
	 *    Вызывается ПЕРЕД отрисовкой кадра.
	 */
	void frameStarted(float timeStep);

	/*!
	 * \brief
	 *    Вызывается ПОСЛЕ отрисовки кадра.
	 */
	void frameEnded();

	/*!
	 * \brief
	 *    Изменяет текущее состояние на новое.
	 * 
	 * \param[in] state
	 *    Указатель на новое состояние.
	 * 
	 * \param[in] context
	 *    Указатель на контекст.
	 */
	void changeState(AStateBase * state, core::foundation::Context * context);

	void pushState(AStateBase * state, core::foundation::Context * context);

	void popState();

private:
	std::vector<AStateBase *> _stateStack;
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_FSM_STATEMANAGER_H
