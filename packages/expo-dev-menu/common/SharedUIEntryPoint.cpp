#include "SharedUIEntryPoint.h"

namespace shared {

SharedUIEntryPoint::SharedUIEntryPoint(std::weak_ptr<RegistryHolder> registryHolder)
  : registryHolder(std::move(registryHolder)) {}

jsi::Value SharedUIEntryPoint::get(jsi::Runtime &rt, const jsi::PropNameID &name) {
  auto cName = name.utf8(rt);
  
  if (cName == "exportSharedUI") {
    auto callback = [this](
      jsi::Runtime &rt,
      const jsi::Value &thisValue,
      const jsi::Value *args,
      size_t count
    ) -> jsi::Value {
      auto strongHolder = this->registryHolder.lock();
      if (strongHolder == nullptr) {
        return jsi::Value::undefined();
      }
      auto entry = ComponentEntry::createFromValue(rt, args[0]);
      strongHolder->updateComponent(std::move(entry));
      return jsi::Value::undefined();
    };
    
    return jsi::Function::createFromHostFunction(
      rt, name, 1, std::move(callback)
    );
  } else if (cName == "markAsRoot") {
    auto callback = [this](
      jsi::Runtime &rt,
      const jsi::Value &thisValue,
      const jsi::Value *args,
      size_t count
    ) -> jsi::Value {
      auto strongHolder = this->registryHolder.lock();
      if (strongHolder == nullptr) {
        return jsi::Value::undefined();
      }
      auto entry = ComponentEntry::createFromValue(rt, args[0]);
      return jsi::Value::undefined();
    };

    return jsi::Function::createFromHostFunction(
      rt, name, 1, std::move(callback)
    );
  }
  
  return jsi::Value::undefined();
}

void SharedUIEntryPoint::set(jsi::Runtime &rt, const jsi::PropNameID &name, const jsi::Value &value) {
  throw jsi::JSError(rt, "Cannot modify the SharedUIEntryPoint object.");
}

std::vector<jsi::PropNameID> SharedUIEntryPoint::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forUtf8(rt, "exportSharedUI"));
  result.push_back(jsi::PropNameID::forUtf8(rt, "markAsRoot"));
  return result;
}

}
