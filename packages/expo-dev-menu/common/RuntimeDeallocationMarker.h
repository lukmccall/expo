#pragma once
#ifdef __cplusplus

#include "RegistryHolder.h"

#include <memory>
#include <jsi/jsi.h>


namespace jsi = facebook::jsi;

namespace shared {

class JSI_EXPORT RuntimeDeallocationMarker : public jsi::HostObject {
public:
  RuntimeDeallocationMarker();
  
  jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;

  void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
  
  std::weak_ptr<RegistryHolder> receiveHolderReference();
  
private:
  std::shared_ptr<RegistryHolder> holder;
};

}

#endif
