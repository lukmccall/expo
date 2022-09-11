#pragma once

#ifdef __cplusplus

#include "RegistryHolder.h"

#include <jsi/jsi.h>
#include <memory>

namespace jsi = facebook::jsi;

namespace shared {
class JSI_EXPORT SharedUIEntryPoint : public jsi::HostObject {
public:
  SharedUIEntryPoint(std::weak_ptr<RegistryHolder> registryHolder);
  
  jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;

  void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

private:
  std::weak_ptr<RegistryHolder> registryHolder;
};
}

#endif // __cplusplus
