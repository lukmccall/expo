#pragma once
#ifdef __cplusplus

#include <string>
#include <vector>

namespace shared {

class ComponentEntry;
class SharedUIRegistry;

class ConnectedComponents {
public:
  ConnectedComponents(std::vector<std::string> components);
  
  std::vector<ComponentEntry> resolve(const SharedUIRegistry &registry);
private:
  std::vector<std::string> components;
};

}

#endif
