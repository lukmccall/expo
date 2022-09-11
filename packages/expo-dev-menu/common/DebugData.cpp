#include "DebugData.h"

namespace shared {

DebugData::DebugData(std::string fileName, unsigned int lineNumber)
  : fileName(std::move(fileName)), lineNumber(lineNumber) {}

std::string DebugData::getLocation() {
  return fileName + " at " + std::to_string(lineNumber);
}
  
}
