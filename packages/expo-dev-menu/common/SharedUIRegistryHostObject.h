#pragma once

#ifdef __cplusplus

#include "RegistryHolder.h"

namespace jsi = facebook::jsi;

namespace shared {
class JSI_EXPORT SharedUIRegistryHostObject : public jsi::HostObject {
public:
  jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;

  void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

  void setRegistyHolderRef(unsigned long long rawPointer);
private:
  std::weak_ptr<RegistryHolder> *registryHolderRef = nullptr;
};
}

#endif // __cplusplus
