#include "playstate.hpp"

#include <sway/game/framework.hpp>
// #include <sway/ois/keycodes.hpp>

#include <stdio.h>

PlayState PlayState::_instance;

void PlayState::enter() {
  printf("PlayState::enter\n");

  auto context = static_cast<game::Framework *>(getContext());

  // auto keyboard = context->getInput()->getDevice<ois::Keyboard>();
  // keyboard->setListener(this);
  // context->getCanvas()->addEventBinding(KeyPress, std::bind(&ois::Keyboard::notifyKeyPressed, keyboard,
  // std::placeholders::_1)); context->getCanvas()->addEventBinding(KeyRelease,
  // std::bind(&ois::Keyboard::notifyKeyReleased, keyboard, keyboard, std::placeholders::_1));

  auto renderSubsystem = getSubsystem<graphics::RenderSubsystem>();
  auto renderQueue = renderSubsystem.value()->getQueueByIdx(0);
  auto renderSubqueue = renderQueue->getSubqueues(graphics::RenderSubqueueGroup_t::kOpaque)[0];

  gapi::ShaderCreateInfoSet shaderCreateInfoSet;
  shaderCreateInfoSet.vs.type = gapi::ShaderType_t::kVertex;
  shaderCreateInfoSet.vs.code = "attribute vec3 attr_position;"
                                "attribute vec4 attr_color;"
                                "varying vec4 color;"
                                "void main() {"
                                "	gl_Position = vec4(attr_position, 1.0);"
                                "	color = attr_color;"
                                "}";
  shaderCreateInfoSet.fs.type = gapi::ShaderType_t::kFragment;
  shaderCreateInfoSet.fs.code = "varying vec4 color;"
                                "void main() {"
                                "	gl_FragColor = color;"
                                "}";
  _material = std::make_shared<graphics::Material>(shaderCreateInfoSet);
  _staticMesh = std::make_shared<graphics::StaticMesh>(renderSubqueue, _material);
}

void PlayState::exit() { printf("PlayState::exit\n"); }

void PlayState::pause() {
  // Empty
}

void PlayState::resume() {
  // Empty
}

void PlayState::frameStarted(float timeStep) {
  // Empty
}

void PlayState::frameEnded() {
  // Empty
}

// void PlayState::onKeyPressed(const ois::KeyboardEventArgs &event) {
//   // if (event.keycode == ois::KeyCodes::kKeyCode_S) {
//   // 	static_cast<game::Framework *>(getContext())->startup(MenuState::getInstance());
//   // }

//   // if (event.keycode == ois::KeyCodes::kKeyCode_Q) {
//   // 	static_cast<game::Framework *>(getContext())->terminate();
//   // }
// }

// void PlayState::onKeyReleased(const ois::KeyboardEventArgs &event) {
//   // Empty
// }

// void PlayState::onMouseButtonDown(const ois::MouseEventArgs &event) {
//   // Empty
// }

// void PlayState::onMouseButtonUp(const ois::MouseEventArgs &event) {
//   // Empty
// }

// void PlayState::onMouseMove(const ois::MouseEventArgs &event) {
//   // Empty
// }
