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

  void startup(fsm::AStateBase *state);

  void terminate();

  void run();

  glx11::CanvasRef_t getCanvas();

  ois::InputDeviceManagerRef_t getInput();

private:
  void initializeCanvas_(const boost::property_tree::ptree &config);

  void initializeRenderSubsystem_(const boost::property_tree::ptree &config);

private:
  glx11::XScreenConnectionRef_t _connection;
  glx11::CanvasRef_t canvas_;
  graphics::RenderSubsystemRef_t renderSubsystem_;
  graphics::RenderQueueRef_t renderQueue_;
  ois::InputDeviceManagerRef_t inputMgr_;
  std::shared_ptr<fsm::StateManager> stateMgr_;

  bool _keepgoing;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FRAMEWORK_H
