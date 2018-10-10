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

	void terminate();

	void run();

	glx11::CanvasRef_t getCanvas();

	ois::InputDeviceManagerRef_t getInput();

	boost::shared_ptr<fsm::StateManager> getState();
	
private:
	void _initializeCanvas(const boost::property_tree::ptree & config);

	void _initializeRenderSubsystem();

private:
	glx11::XScreenConnectionRef_t _connection;
	glx11::CanvasRef_t _canvas;
	graphics::RenderSubsystemRef_t _renderSubsystem;
	ois::InputDeviceManagerRef_t _inputMgr;
	boost::shared_ptr<fsm::StateManager> _stateMgr;

	bool _keepgoing;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_FRAMEWORK_H
