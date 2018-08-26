#ifndef SWAY_GAME_FRAMEWORK_H
#define SWAY_GAME_FRAMEWORK_H

#include <sway/game/fsm/statebase.h>
#include <sway/game/fsm/statemanager.h>
#include <sway/game/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class Framework : public core::foundation::Context {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Framework();

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~Framework();

	void startup(fsm::IStateBase * state);

private:
	boost::shared_ptr<fsm::StateManager> _stateMgr;
	boost::shared_ptr<graphics::RenderSubsystem> _renderSubsystem;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_FRAMEWORK_H
