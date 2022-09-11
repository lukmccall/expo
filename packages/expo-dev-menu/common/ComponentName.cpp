#include "ComponentName.h"

namespace shared {

ComponentName::ComponentName(std::string name)
  : name(std::move(name)) {}

bool ComponentName::operator==(const ComponentName &other) const {
  return other.name == this->name;
}

bool ComponentName::operator==(const std::string &other) const {
  return other == this->name;
}

std::size_t ComponentNameHash::operator()(const ComponentName &componentName) const {
  return std::hash<std::string>{}(componentName.name);
}

}
