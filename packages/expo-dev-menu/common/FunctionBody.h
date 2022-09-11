#pragma once
#ifdef __cplusplus

#include <string>

namespace shared {

class FunctionBody {
public:
  FunctionBody(std::string body);
  
  std::string prepare();
private:
  std::string body;
};

}

#endif

