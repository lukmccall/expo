#include "RegistryHolder.h"

namespace shared {

RegistryHolder::RegistryHolder()
  : registry(std::make_unique<SharedUIRegistry>()) {}

void RegistryHolder::addListener(std::shared_ptr<SharedUIRegistryListener> listener) {
  registry->addListener(std::move(listener));
}

void RegistryHolder::removeListener(std::shared_ptr<SharedUIRegistryListener> listener) {
  registry->removeListener(std::move(listener));
}

SharedUIRegistry &RegistryHolder::get() const {
  return *registry.get();
}

void RegistryHolder::updateComponent(ComponentEntry entry) {
  registry->updateComponent(std::move(entry));
}

}
