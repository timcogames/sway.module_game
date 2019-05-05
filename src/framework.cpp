#include <sway/game/framework.h>
#include <sway/game/settings.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Framework::Framework()
	: _keepgoing(true) {
	auto settings = std::make_shared<Settings>();

	_initializeCanvas(settings->getChild("Window"));
	_initializeRenderSubsystem(settings->getChild("Gapi"));

	_inputMgr = std::make_shared<ois::InputDeviceManager>(_connection->getDisplay(), _canvas->getWindowHandle());
	_stateMgr = std::make_shared<fsm::StateManager>();
}

Framework::~Framework() {
	// Empty
}

void Framework::startup(fsm::AStateBase * state) {
	_stateMgr->changeState(state, this);
}

void Framework::terminate() {
	_keepgoing = false;
}

void Framework::run() {
	while (_canvas->eventLoop(_keepgoing)) {
		_canvas->getContext()->makeCurrent();

		_stateMgr->frameStarted(0);
		_renderSubsystem->render();
		_stateMgr->frameEnded();

		_canvas->getContext()->present();
		_canvas->getContext()->doneCurrent();
	}
}

void Framework::_initializeCanvas(const boost::property_tree::ptree & config) {
	glx11::WindowInitialInfo windowInfo;
	windowInfo.title = "seeker";
	windowInfo.size.normal = math::size2i_t(config.get<int>("Width"), config.get<int>("Height"));
	windowInfo.size.min = math::size2i_t(config.get<int>("MinWidth", 640), config.get<int>("MinHeight", 480));
	windowInfo.size.max = math::size2i_t(config.get<int>("MaxWidth", 1024), config.get<int>("MaxHeight", 768));
	windowInfo.fullscreen = config.get<bool>("Fullscreen");
	windowInfo.resizable = true;

	_connection = std::make_shared<glx11::XScreenConnection>();
	_canvas = std::make_shared<glx11::Canvas>(_connection, windowInfo);

	_canvas->show();
	_canvas->getContext()->makeCurrent();
}

void Framework::_initializeRenderSubsystem(const boost::property_tree::ptree & config) {
	auto plugname = core::misc::format("%s.%s",
		config.get<std::string>("Name").c_str(), config.get<std::string>("Version").c_str());

	_renderSubsystem = std::make_shared<graphics::RenderSubsystem>(plugname, this);
	_renderQueue = _renderSubsystem->createQueue();
	_renderQueue->setPriority(core::intrusive::kPriority_Normal);
	_renderQueue->addSubqueue(std::make_shared<graphics::RenderSubqueue>(graphics::RenderSubqueueGroup_t::kOpaque));

	this->registerObject(_renderSubsystem.get());
}

glx11::CanvasRef_t Framework::getCanvas() {
	return _canvas;
}

ois::InputDeviceManagerRef_t Framework::getInput() {
	return _inputMgr;
}

NAMESPACE_END(game)
NAMESPACE_END(sway)
