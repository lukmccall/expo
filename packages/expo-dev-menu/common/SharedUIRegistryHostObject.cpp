#include "SharedUIRegistryHostObject.h"

namespace shared {

jsi::Value SharedUIRegistryHostObject::get(jsi::Runtime &rt, const jsi::PropNameID &name) {
  auto cName = name.utf8(rt);
  
  if (cName == "getComponentData") {
    auto callback = [this](
      jsi::Runtime &rt,
      const jsi::Value &thisValue,
      const jsi::Value *args,
      size_t count
    ) -> jsi::Value {
      if (registryHolderRef == nullptr) {
        return jsi::Value::undefined();
      }
      
      auto strongRegistryHolder = registryHolderRef->lock();
      if (strongRegistryHolder == nullptr) {
        return jsi::Value::undefined();
      }
      
      auto& components = strongRegistryHolder->get().components;
      
      auto componentName = ComponentName(args[0].asString(rt).utf8(rt));
      auto result = components.find(componentName);
      if (result == components.end()) {
        return jsi::Value::undefined();
      }
      auto& component = result->second;
  
      auto jsObject = jsi::Object(rt);
      jsObject.setProperty(rt, "hash", jsi::String::createFromUtf8(rt, component.getHash()));
      jsObject.setProperty(rt, "body", jsi::String::createFromUtf8(rt, component.getFunctionBody()));
      
      auto childrenArray = jsi::Array(rt, component.connectedComponents.components.size());
      for (size_t i = 0; i < component.connectedComponents.components.size(); i++) {
        childrenArray.setValueAtIndex(rt, i, jsi::String::createFromUtf8(rt, component.connectedComponents.components[i]));
      }
      jsObject.setProperty(rt, "children", std::move(childrenArray));
      
      return std::move(jsObject);
    };
    
    return jsi::Function::createFromHostFunction(
      rt, name, 1, std::move(callback)
    );
  }
  
  return jsi::Value::undefined();
}

void SharedUIRegistryHostObject::set(jsi::Runtime &rt, const jsi::PropNameID &name, const jsi::Value &value) {
  throw jsi::JSError(rt, "Cannot modify the SharedUIRegistryHostObject object.");
}

std::vector<jsi::PropNameID> SharedUIRegistryHostObject::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forUtf8(rt, "getComponentData"));
  return result;
}

void SharedUIRegistryHostObject::setRegistyHolderRef(unsigned long long rawPointer) {
  if (rawPointer == 0) {
    registryHolderRef = nullptr;
    return;
  }
  registryHolderRef = (std::weak_ptr<RegistryHolder> *)rawPointer;
}

}
