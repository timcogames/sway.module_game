#ifndef SWAY_GAME_SCENENODE_HPP
#define SWAY_GAME_SCENENODE_HPP

#include <sway/core/container/node.hpp>
#include <sway/core/detail/enumutils.hpp>
#include <sway/core/utils/traverser.hpp>
#include <sway/core/utils/visitable.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class SceneNodeTraverser : public core::utils::Traverser {
public:
  MTHD_OVERRIDE(u32_t visit([[maybe_unused]] core::utils::Visitable *node)) {
    return core::detail::toUnderlying(core::utils::Traverser::Action::CONTINUE);
  }
};

class SceneNode : public core::container::Node {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  SceneNode() {}

  ~SceneNode() = default;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_SCENENODE_HPP
