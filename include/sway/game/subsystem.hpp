#ifndef SWAY_GAME_SUBSYSTEM_HPP
#define SWAY_GAME_SUBSYSTEM_HPP

#include <sway/core.hpp>

#include <map>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class Subsystem : public core::foundation::Context {
public:
  using ObjectMap_t = std::map<std::string, core::foundation::Object *>;

  Subsystem() {}

  ~Subsystem() { objects_.clear(); }

  void registerObject(core::foundation::Object *object) {
    if (!object) {
      throw core::runtime::exceptions::ArgumentNullException("object");
    }

    objects_.insert(std::make_pair("object->getClassname()", object));
  }

  void unregisterObject(const std::string &objectClassName) {
    ObjectMap_t::const_iterator iter = objects_.find(objectClassName);
    if (iter != objects_.end()) {
      objects_.erase(iter);
    }
  }

  core::foundation::Object *getObject(const std::string &objectClassName) const {
    ObjectMap_t::const_iterator iter = objects_.find(objectClassName);
    if (iter != objects_.end()) {
      return iter->second;
    }

    return 0;
  }

private:
  ObjectMap_t objects_; /*!< Контейнер объектов. */
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif  // SWAY_GAME_SUBSYSTEM_HPP
