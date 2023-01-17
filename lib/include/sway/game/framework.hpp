#ifndef SWAY_GAME_FRAMEWORK_HPP
#define SWAY_GAME_FRAMEWORK_HPP

#include <sway/core/foundation/context.hpp>
#include <sway/game/fsm/statebase.hpp>
#include <sway/game/fsm/statemanager.hpp>
#include <sway/game/prereqs.hpp>
#include <sway/ois.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class Framework : public core::foundation::Context {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  Framework();

  ~Framework() = default;

  void startup(fsm::StateBase *state);

  void terminate();

  void run();

  auto getCanvas() -> glx11::CanvasRef_t { return canvas_; }

  auto getInput() -> ois::InputDeviceManagerRef_t { return inputMgr_; }

private:
  void initializeCanvas_(/*const boost::property_tree::ptree &config*/);

  void initializeRenderSubsystem_(/*const boost::property_tree::ptree &config*/);

  glx11::XScreenConnectionRef_t connection_;
  glx11::CanvasRef_t canvas_;
  graphics::RenderSubsystemRef_t renderSubsystem_;
  graphics::RenderQueueRef_t renderQueue_;
  ois::InputDeviceManagerRef_t inputMgr_;
  std::shared_ptr<fsm::StateManager> stateMgr_;

  bool keepgoing_;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FRAMEWORK_HPP
