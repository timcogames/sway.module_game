#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <sway/game.hpp>
#include <sway/gapi.hpp>
#include <sway/graphics.hpp>
// #include <sway/ois.hpp>

using namespace sway;

class PlayState : public game::fsm::AStateBase /*, public ois::InputListener*/ {
public:
  static PlayState _instance;
  static PlayState *getInstance() { return &_instance; }

  PlayState() = default;

  virtual ~PlayState() = default;

  MTHD_OVERRIDE(void enter());

  MTHD_OVERRIDE(void exit());

  MTHD_OVERRIDE(void pause());

  MTHD_OVERRIDE(void resume());

  MTHD_OVERRIDE(void frameStarted(float timeStep));

  MTHD_OVERRIDE(void frameEnded());

  // virtual void onKeyPressed(const ois::KeyboardEventArgs &event) override;

  // virtual void onKeyReleased(const ois::KeyboardEventArgs &event) override;

  // virtual void onMouseButtonDown(const ois::MouseEventArgs &event) override;

  // virtual void onMouseButtonUp(const ois::MouseEventArgs &event) override;

  // virtual void onMouseMove(const ois::MouseEventArgs &event) override;

private:
  graphics::MaterialRef_t _material;
  graphics::StaticMeshRef_t _staticMesh;
};

#endif  // PLAYSTATE_HPP
