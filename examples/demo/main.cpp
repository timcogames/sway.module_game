#include "playstate.hpp"

#include <sway/game.hpp>
// #include <sway/ois.hpp>

#include <memory>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  auto framework = std::make_shared<game::Framework>();
  framework->getInput()->registerDevice<ois::Keyboard>();
  // framework->getInput()->registerDevice<ois::Mouse>();
  framework->startup(PlayState::getInstance());
  framework->run();
  return 0;
}
