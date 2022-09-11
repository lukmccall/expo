#include "SharedUIRegistry.h"

#include <algorithm>

namespace shared {

void SharedUIRegistry::addListener(std::shared_ptr<SharedUIRegistryListener> listener) {
  listeners.push_back(std::move(listener));
}

void SharedUIRegistry::removeListener(std::shared_ptr<SharedUIRegistryListener> listener) {
  auto toRemove = std::find(
    listeners.begin(),
    listeners.end(),
    listener
  );
  
  if (toRemove != listeners.end()) {
    listeners.erase(toRemove);
  }
}

void SharedUIRegistry::updateComponent(ComponentEntry entry) {
  ComponentName &name = entry.name;
  
  auto result = components.find(name);
  if (result == components.end()) {
    components.insert({name, std::move(entry)});
    return;
  }
  
  auto& current = result->second;
  if (current.hash == entry.hash) {
    return;
  }
  
  result->second = entry;
  for (auto& listener : listeners) {
    listener->update(name);
  }
}

}
