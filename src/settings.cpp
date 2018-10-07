#include <sway/game/settings.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

Settings::Settings() {
	try {
		boost::filesystem::path path("/home/bonus85/Projects/game.seeker/config/settings.ini");
		boost::property_tree::read_ini(path.string(), _properties);
	}
	catch(boost::property_tree::ptree_bad_data & ex) {
		std::cout << "Bad data: " << ex.what() << std::endl;
	}
	catch(boost::property_tree::ptree_bad_path & ex) {
		std::cout << "Bad path: " << ex.what() << std::endl;
	}
	catch(boost::property_tree::ptree_error & ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	catch(...) {
		throw;
	}
}

Settings::~Settings() {
	// Empty
}

NAMESPACE_END(game)
NAMESPACE_END(sway)
