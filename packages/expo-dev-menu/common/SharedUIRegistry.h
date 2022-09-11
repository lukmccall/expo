#pragma once
#ifdef __cplusplus

#include "ComponentName.h"
#include "ComponentEntry.h"

#include <jsi/jsi.h>
#include <memory>
#include <vector>
#include <unordered_map>

namespace jsi = facebook::jsi;

namespace shared {
class SharedUIRegistryHostObject;

class SharedUIRegistryListener {
public:
  virtual void update(const ComponentName &componentName) = 0;
};

class SharedUIRegistry {
public:
  void addListener(std::shared_ptr<SharedUIRegistryListener> listener);
  
  void removeListener(std::shared_ptr<SharedUIRegistryListener> listener);
    
  void updateComponent(ComponentEntry entry);

private:
  std::unordered_map<ComponentName, ComponentEntry, ComponentNameHash> components;
  std::vector<std::shared_ptr<SharedUIRegistryListener>> listeners;
  
  friend ConnectedComponents;
  friend SharedUIRegistry
};

}

#endif
