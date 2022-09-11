#pragma once
#ifdef __cplusplus

#include <string>
#include <functional>

namespace shared {

class ComponentNameHash;

class ComponentName {
public:
  ComponentName(std::string name);
  
  bool operator==(const ComponentName &other) const;
  bool operator==(const std::string &other) const;
  
private:
  std::string name;
  
  friend ComponentNameHash;
};

struct ComponentNameHash {
  std::size_t operator()(const ComponentName &componentName) const;
};

}

#endif
