#include "RuntimeDeallocationMarker.h"

namespace shared {

RuntimeDeallocationMarker::RuntimeDeallocationMarker() : holder(std::make_shared<RegistryHolder>()) {}

jsi::Value RuntimeDeallocationMarker::get(jsi::Runtime &, const jsi::PropNameID &name) {
  return jsi::Value::undefined();
}

void RuntimeDeallocationMarker::set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) {
  
}

std::vector<jsi::PropNameID> RuntimeDeallocationMarker::getPropertyNames(jsi::Runtime &rt) {
  return {};
}

std::weak_ptr<RegistryHolder> RuntimeDeallocationMarker::receiveHolderReference() {
  return holder;
}
}
