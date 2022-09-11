#include "ConnectedComponents.h"

#include "ComponentName.h"
#include "ComponentEntry.h"
#include "SharedUIRegistry.h"

namespace shared {

ConnectedComponents::ConnectedComponents(std::vector<std::string> components)
  : components(std::move(components)) {}

std::vector<ComponentEntry> ConnectedComponents::resolve(const SharedUIRegistry &registry) {
  std::vector<ComponentEntry> result;
  result.reserve(components.size());
  
  for (auto& componentStringName : components) {
    ComponentName componentName(componentStringName);
    auto component = registry.components.find(componentStringName)->second;
    result.push_back(component);
  }
  
  return result;
}

}
