#ifndef SWAY_GAME_FSM_STATEBASE_HPP
#define SWAY_GAME_FSM_STATEBASE_HPP

#include <sway/game/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class AStateBase {
public:
  /*!
   * \brief
   *    Конструктор класса.
   */
  AStateBase() = default;

  /*!
   * \brief
   *    Деструктор класса.
   */
  virtual ~AStateBase() = default;

  /*!
   * \brief
   *    Выполняться при входе в состояние.
   */
  virtual void enter() = 0;

  /*!
   * \brief
   *    Выполняться при выходе из состояния.
   */
  virtual void exit() = 0;

  virtual void pause() = 0;

  virtual void resume() = 0;

  virtual void frameStarted(float timeStep) = 0;

  virtual void frameEnded() = 0;

  /*!
   * \brief
   *    Устанавливает контекст.
   *
   * \param[in] context
   *    Указатель на контекст.
   */
  void setContext(core::foundation::Context *context) { context_ = context; }

  core::foundation::Context *getContext() { return context_; }

  /*!
   * \brief
   *    Получает подсистему.
   */
  template <class OBJ>
  OBJ *getSubsystem() const {
    return static_cast<OBJ *>(context_->getObject(OBJ::getObjectMetadata()->getClassName()));
  }

private:
  core::foundation::Context *context_; /*!< Контекст. */
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FSM_STATEBASE_H
