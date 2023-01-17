#include <sway/game/framework.hpp>
#include <sway/game/settings.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Framework::Framework()
    : keepgoing_(true) {
  // auto settings = std::make_shared<Settings>();

  initializeCanvas_(/*settings->getChild("Window")*/);
  initializeRenderSubsystem_(/*settings->getChild("Gapi")*/);

  inputMgr_ = std::make_shared<ois::InputDeviceManager>(connection_->getDisplay(), canvas_->getWindowHandle());
  stateMgr_ = std::make_shared<fsm::StateManager>();
}

void Framework::startup(fsm::StateBase *state) { stateMgr_->changeState(state, this); }

void Framework::terminate() { keepgoing_ = false; }

void Framework::run() {
  while (canvas_->eventLoop(keepgoing_)) {
    canvas_->getContext()->makeCurrent();

    stateMgr_->frameStarted(0);
    renderSubsystem_->render();
    stateMgr_->frameEnded();

    canvas_->getContext()->present();
    canvas_->getContext()->doneCurrent();
  }
}

void Framework::initializeCanvas_(/*const boost::property_tree::ptree &config*/) {
  glx11::WindowInitialInfo windowInfo;
  windowInfo.title = "seeker";
  windowInfo.size.normal =
      math::size2i_t(640, 480);  // math::size2i_t(config.get<int>("Width"), config.get<int>("Height"));
  windowInfo.size.min =
      math::size2i_t(640, 480);  // math::size2i_t(config.get<int>("MinWidth", 640), config.get<int>("MinHeight", 480));
  windowInfo.size.max = math::size2i_t(
      640, 480);  // math::size2i_t(config.get<int>("MaxWidth", 1024), config.get<int>("MaxHeight", 768));
  windowInfo.fullscreen = false;  // config.get<bool>("Fullscreen");
  windowInfo.resizable = true;

  connection_ = std::make_shared<glx11::XScreenConnection>();
  canvas_ = std::make_shared<glx11::Canvas>(connection_, windowInfo);

  canvas_->show();
  canvas_->getContext()->makeCurrent();
}

void Framework::initializeRenderSubsystem_(/*const boost::property_tree::ptree &config*/) {
  // auto plugname =
  //     core::misc::format("%s.%s", config.get<std::string>("Name").c_str(),
  //     config.get<std::string>("Version").c_str());

  renderSubsystem_ = std::make_shared<graphics::RenderSubsystem>(
      "/Users/apriori85/Documents/Projects/sway.module_game/bin/module_gapi_gl.dylib.0.16.34", this);
  renderQueue_ = renderSubsystem_->createQueue();
  renderQueue_->setPriority(core::intrusive::Priority_Normal);
  renderQueue_->addSubqueue(std::make_shared<graphics::RenderSubqueue>(graphics::RenderSubqueueGroup_t::kOpaque));

  registerSubsystem(renderSubsystem_);
}

NAMESPACE_END(game)
NAMESPACE_END(sway)
