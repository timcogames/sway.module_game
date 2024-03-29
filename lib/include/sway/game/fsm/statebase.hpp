#ifndef SWAY_GAME_FSM_STATEBASE_HPP
#define SWAY_GAME_FSM_STATEBASE_HPP

#include <sway/game/prereqs.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class StateBase {
public:
  StateBase() = default;

  virtual ~StateBase() = default;

  /**
   * @brief Выполняться при входе в состояние.
   */
  PURE_VIRTUAL(void enter());

  /**
   * @brief Выполняться при выходе из состояния.
   */
  PURE_VIRTUAL(void exit());

  PURE_VIRTUAL(void pause());

  PURE_VIRTUAL(void resume());

  PURE_VIRTUAL(void frameStarted(float timestep));

  PURE_VIRTUAL(void frameEnded());

  /**
   * @brief Устанавливает контекст.
   *
   * @param[in] context Указатель на контекст.
   */
  void setContext(core::foundation::Context *context) { context_ = context; }

  auto getContext() -> core::foundation::Context * { return context_; }

  /**
   * @brief Получает подсистему.
   */
  template <class OBJ>
  auto getSubsystem() const -> std::optional<std::shared_ptr<OBJ>> {
    return context_->getSubsystem<OBJ>(OBJ::getObjectClassMetadata()->getClassname());
  }

private:
  core::foundation::Context *context_;  // Контекст.
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FSM_STATEBASE_HPP
