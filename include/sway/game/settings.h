#ifndef SWAY_GAME_SETTINGS_H
#define SWAY_GAME_SETTINGS_H

#include <sway/game/prereqs.h>
#include <boost/filesystem.hpp> // boost::filesystem::path

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class Settings : boost::noncopyable {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Settings();

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~Settings();

	template<typename TYPE>
	const TYPE get(const std::string & name) const {
		return _properties.get<TYPE>(name);
	}

	const boost::property_tree::ptree getChild(const std::string & name) const {
		return _properties.get_child(name);
	}

private:
	boost::property_tree::ptree _properties;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_SETTINGS_H
