#include <sway/game/framework.h>
#include <sway/game/settings.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Framework::Framework()
	: _keepgoing(true) {
	auto settings = boost::make_shared<Settings>();

	_initializeCanvas(settings->getChild("window"));
	_initializeRenderSubsystem();

	_inputMgr = boost::make_shared<ois::InputDeviceManager>(_connection->getDisplay(), _canvas->getWindowHandle());
	_stateMgr = boost::make_shared<fsm::StateManager>();
}

Framework::~Framework() {
	// Empty
}

void Framework::startup(fsm::IStateBase * state) {
	_stateMgr->changeState(state, this);
}

void Framework::terminate() {
	_keepgoing = false;
}

void Framework::run() {
	while (_canvas->eventLoop(_keepgoing)) {
		_canvas->getContext()->makeCurrent();

		_stateMgr->frameStarted(0);
		_stateMgr->frameEnded();

		_canvas->getContext()->present();
		_canvas->getContext()->doneCurrent();
	}
}

void Framework::_initializeCanvas(const boost::property_tree::ptree & config) {
	glx11::WindowInitialInfo windowInfo;
	windowInfo.title = "seeker";
	windowInfo.size.normal = math::size2i_t(config.get<int>("width"), config.get<int>("height"));
	windowInfo.size.min = math::size2i_t(config.get<int>("min_width", 640), config.get<int>("min_height", 480));
	windowInfo.size.max = math::size2i_t(config.get<int>("max_width", 1024), config.get<int>("max_height", 768));
	windowInfo.fullscreen = config.get<bool>("fullscreen");
	windowInfo.resizable = true;

	_connection = boost::make_shared<glx11::XScreenConnection>();
	_canvas = boost::make_shared<glx11::Canvas>(_connection, windowInfo);

	_canvas->show();
	_canvas->getContext()->makeCurrent();
}

void Framework::_initializeRenderSubsystem() {
	char path[PATH_MAX + 1];
	strncpy(path, "/home/bonus85/Projects/game.seeker/bin", PATH_MAX);

	graphics::PluginDescriptor desc;
	desc.version = core::Version(0, 13, 32);
	desc.fullname = boost::str(boost::format("%s/module_gapi_gl.so.%d.%d.%d") % path
		% desc.version.getMajor() % desc.version.getMinor() % desc.version.getPatch());

	_renderSubsystem = boost::make_shared<graphics::RenderSubsystem>(desc, this);
	this->registerObject(_renderSubsystem.get());
}

glx11::CanvasRef_t Framework::getCanvas() {
	return _canvas;
}

ois::InputDeviceManagerRef_t Framework::getInput() {
	return _inputMgr;
}

boost::shared_ptr<fsm::StateManager> Framework::getState() {
	return _stateMgr;
}

NAMESPACE_END(game)
NAMESPACE_END(sway)
