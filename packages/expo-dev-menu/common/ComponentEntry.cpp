#include "ComponentEntry.h"

namespace shared {

ComponentEntry::ComponentEntry(
  ComponentName name,
  FunctionBody body,
  ConnectedComponents connectedComponents,
  ComponentHash hash,
  DebugData debugData
) : name(std::move(name)),
  body(std::move(body)),
  connectedComponents(std::move(connectedComponents)),
  hash(std::move(hash)),
  debugData(std::move(debugData)) {}

bool ComponentEntry::operator==(const ComponentEntry &other) {
  return this->name == other.name;
}

std::string ComponentEntry::getDebugInformation() {
  return debugData.getLocation();
}

std::string ComponentEntry::getFunctionBody() {
  return body.prepare();
}

std::string ComponentEntry::getHash() {
  return hash.toString();
}

std::vector<ComponentEntry> ComponentEntry::reciveConnectedComponents(const SharedUIRegistry &registry) {
  return connectedComponents.resolve(registry);
}

ComponentEntry ComponentEntry::createFromValue(jsi::Runtime &rt, const jsi::Value& jsValue) {
  auto object = jsValue.asObject(rt);
  
  auto bodyString = object.getProperty(rt, "_string").asString(rt).utf8(rt);
  
  auto fileName = object.getProperty(rt, "_fileName").asString(rt).utf8(rt);
  auto lineNumber = (unsigned int) object.getProperty(rt, "_lineNumber").asNumber();
  
  auto nameString = object.getProperty(rt, "_name").asString(rt).utf8(rt);
  auto hash = object.getProperty(rt, "_hash").asString(rt).utf8(rt);
  
  auto uiClouser = object.getProperty(rt, "_uiClosure").asObject(rt).asArray(rt);
  std::vector<std::string> connectedComponents;
  
  auto size = uiClouser.size(rt);
  connectedComponents.reserve(size);
  
  for (size_t i = 0; i < size; i++) {
    auto componentName = uiClouser.getValueAtIndex(rt, i).asString(rt).utf8(rt);
    connectedComponents.push_back(std::move(componentName));
  }
  
  return ComponentEntry(
    ComponentName(std::move(nameString)),
    FunctionBody(std::move(bodyString)),
    ConnectedComponents(std::move(connectedComponents)),
    ComponentHash(std::move(hash)),
    DebugData(std::move(fileName), lineNumber)
  );
}

}
