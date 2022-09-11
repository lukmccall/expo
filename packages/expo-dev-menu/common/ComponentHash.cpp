#include "ComponentHash.h"

namespace shared {

ComponentHash::ComponentHash(std::string hash)
  : hash(std::move(hash)) {}

bool ComponentHash::operator==(const ComponentHash &other) {
  return other.hash == this->hash;
}

std::string ComponentHash::toString() {
  return hash;
}

}
