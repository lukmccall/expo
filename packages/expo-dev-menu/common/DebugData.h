#pragma once
#ifdef __cplusplus

#include <string>

namespace shared {

class DebugData {
public:
  DebugData(std::string fileName, unsigned int lineNumber);
  
  std::string getLocation();
private:
  std::string fileName;
  unsigned int lineNumber;
};

}

#endif

