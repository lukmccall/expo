#include "FunctionBody.h"

namespace shared {

FunctionBody::FunctionBody(std::string body)
  : body(std::move(body)) {}

std::string FunctionBody::prepare() {
  return "(jsThis, React) => (" + body + ")";
}

}
