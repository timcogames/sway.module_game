#ifndef SWAY_GAME_FSM_STATEMANAGER_HPP
#define SWAY_GAME_FSM_STATEMANAGER_HPP

#include <sway/game/fsm/statebase.hpp>
#include <sway/game/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)
NAMESPACE_BEGIN(fsm)

class StateManager {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  StateManager();

  /**
   * @brief Деструктор класса.
   */
  ~StateManager();

  /**
   * @brief Вызывается ПЕРЕД отрисовкой кадра.
   */
  void frameStarted(float timeStep);

  /**
   * @brief Вызывается ПОСЛЕ отрисовки кадра.
   */
  void frameEnded();

  /**
   * @brief Изменяет текущее состояние на новое.
   *
   * @param[in] state Указатель на новое состояние.
   * @param[in] context Указатель на контекст.
   */
  void changeState(StateBase *state, core::foundation::Context *context);

  void pushState(StateBase *state, core::foundation::Context *context);

  void popState();

private:
  std::vector<StateBase *> stateStack_;
};

NAMESPACE_END(fsm)
NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_FSM_STATEMANAGER_HPP
