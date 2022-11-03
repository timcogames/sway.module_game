#ifndef SWAY_GAME_FSM_STATEBASE_HPP
#define SWAY_GAME_FSM_STATEBASE_HPP

#include <sway/game/prereqs.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class AStateBase {
public:
  /**
   * @brief Конструктор класса.
   *
   */
  AStateBase() = default;

  /**
   * @brief Деструктор класса.
   *
   */
  virtual ~AStateBase() = default;

  /**
   * @brief Выполняться при входе в состояние.
   *
   */
  PURE_VIRTUAL(void enter());

  /**
   * @brief Выполняться при выходе из состояния.
   *
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
   *
   */
  void setContext(core::foundation::Context *context) { context_ = context; }

  core::foundation::Context *getContext() { return context_; }

  /**
   * @brief Получает подсистему.
   *
   */
  template <class OBJ>
  std::optional<std::shared_ptr<OBJ>> getSubsystem() const {
    return context_->getSubsystem<OBJ>(OBJ::getObjectClassMetadata()->getClassname());
  }

private:
  core::foundation::Context *context_; /*!< Контекст. */
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FSM_STATEBASE_HPP
