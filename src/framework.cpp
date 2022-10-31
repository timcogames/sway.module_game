#include <sway/game/framework.h>
#include <sway/game/settings.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Framework::Framework()
    : _keepgoing(true) {
  auto settings = std::make_shared<Settings>();

  initializeCanvas_(settings->getChild("Window"));
  initializeRenderSubsystem_(settings->getChild("Gapi"));

  inputMgr_ = std::make_shared<ois::InputDeviceManager>(_connection->getDisplay(), canvas_->getWindowHandle());
  stateMgr_ = std::make_shared<fsm::StateManager>();
}

Framework::~Framework() {
  // Empty
}

void Framework::startup(fsm::AStateBase *state) { stateMgr_->changeState(state, this); }

void Framework::terminate() { _keepgoing = false; }

void Framework::run() {
  while (canvas_->eventLoop(_keepgoing)) {
    canvas_->getContext()->makeCurrent();

    stateMgr_->frameStarted(0);
    renderSubsystem_->render();
    stateMgr_->frameEnded();

    canvas_->getContext()->present();
    canvas_->getContext()->doneCurrent();
  }
}

void Framework::initializeCanvas_(const boost::property_tree::ptree &config) {
  glx11::WindowInitialInfo windowInfo;
  windowInfo.title = "seeker";
  windowInfo.size.normal = math::size2i_t(config.get<int>("Width"), config.get<int>("Height"));
  windowInfo.size.min = math::size2i_t(config.get<int>("MinWidth", 640), config.get<int>("MinHeight", 480));
  windowInfo.size.max = math::size2i_t(config.get<int>("MaxWidth", 1024), config.get<int>("MaxHeight", 768));
  windowInfo.fullscreen = config.get<bool>("Fullscreen");
  windowInfo.resizable = true;

  _connection = std::make_shared<glx11::XScreenConnection>();
  canvas_ = std::make_shared<glx11::Canvas>(_connection, windowInfo);

  canvas_->show();
  canvas_->getContext()->makeCurrent();
}

void Framework::initializeRenderSubsystem_(const boost::property_tree::ptree &config) {
  auto plugname =
      core::misc::format("%s.%s", config.get<std::string>("Name").c_str(), config.get<std::string>("Version").c_str());

  renderSubsystem_ = std::make_shared<graphics::RenderSubsystem>(plugname, this);
  renderQueue_ = renderSubsystem_->createQueue();
  renderQueue_->setPriority(core::intrusive::kPriority_Normal);
  renderQueue_->addSubqueue(std::make_shared<graphics::RenderSubqueue>(graphics::RenderSubqueueGroup_t::kOpaque));

  this->registerObject(renderSubsystem_.get());
}

glx11::CanvasRef_t Framework::getCanvas() { return canvas_; }

ois::InputDeviceManagerRef_t Framework::getInput() { return inputMgr_; }

NAMESPACE_END(game)
NAMESPACE_END(sway)
