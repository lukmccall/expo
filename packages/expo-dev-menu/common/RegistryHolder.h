#pragma once
#ifdef __cplusplus

#include "SharedUIRegistry.h"

#include <jsi/jsi.h>

namespace jsi = facebook::jsi;

namespace shared {
class RegistryHolder {
public:
  RegistryHolder();
  
  void addListener(std::shared_ptr<SharedUIRegistryListener> listener);
  
  void removeListener(std::shared_ptr<SharedUIRegistryListener> listener);

  SharedUIRegistry &get() const;
  
  void updateComponent(ComponentEntry entry);

private:
  std::unique_ptr<SharedUIRegistry> registry;
};
}

#endif
