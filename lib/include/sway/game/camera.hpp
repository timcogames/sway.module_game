#ifndef SWAY_GAME_CAMERA_HPP
#define SWAY_GAME_CAMERA_HPP

#include <sway/math.hpp>
#include <sway/math/extensions/projection.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class Camera {
public:
  Camera() {
    float const aspectRatio = 1.0;

    math::Projection projection;
    projmat_ = projection.ortho(-1.0 * aspectRatio, -1.0, 1.0 * aspectRatio, 1.0, 0.0, 100.0);
  }

  ~Camera() = default;

  auto getViewMat4f() -> math::mat4f_t { return viewmat_; }

  auto getProjMat4f() -> math::mat4f_t { return projmat_; }

private:
  math::mat4f_t viewmat_;
  math::mat4f_t projmat_;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_CAMERA_HPP
