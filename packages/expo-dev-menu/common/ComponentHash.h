#pragma once
#ifdef __cplusplus

#include <string>

namespace shared {

class ComponentHash {
public:
  ComponentHash(std::string hash);
  
  bool operator==(const ComponentHash &other);
  
  std::string toString();
private:
  std::string hash;
};

}

#endif
