#pragma once
#ifdef __cplusplus

#include "ComponentName.h"
#include "FunctionBody.h"
#include "ConnectedComponents.h"
#include "ComponentHash.h"
#include "DebugData.h"

#include <jsi/jsi.h>

namespace jsi = facebook::jsi;

namespace shared {

class SharedUIRegistry;
class SharedUIRegistryHostObject;

class ComponentEntry {
public:
  ComponentEntry(
    ComponentName name,
    FunctionBody body,
    ConnectedComponents connectedComponents,
    ComponentHash hash,
    DebugData debugData
  );
  
  bool operator==(const ComponentEntry &other);
  
  std::string getDebugInformation();
  
  std::string getFunctionBody();
  
  std::string getHash();
  
  std::vector<ComponentEntry> reciveConnectedComponents(const SharedUIRegistry &registry);
  
  static ComponentEntry createFromValue(jsi::Runtime &rt, const jsi::Value& jsValue);
  
private:
  ComponentName name;
  FunctionBody body;
  ConnectedComponents connectedComponents;
  ComponentHash hash;
  DebugData debugData;
  
  friend SharedUIRegistry;
  friend SharedUIRegistryHostObject;
};

}

#endif
