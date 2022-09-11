#include "JSIInstaller.h"
#include "SharedUIEntryPoint.h"
#include "RuntimeDeallocationMarker.h"
#include "SharedUIRegistryHostObject.h"

#include <memory>

namespace shared {
void installSharedUIEntryPoint(jsi::Runtime *runtime, std::weak_ptr<RegistryHolder> registyHolder) {
  auto& rt = *runtime;
  
  rt
    .global()
    .setProperty(
                 rt,
                 "SharedUIEntryPoint",
                 jsi::Object::createFromHostObject(rt, std::make_shared<SharedUIEntryPoint>(std::move(registyHolder)))
                 );
}

std::weak_ptr<RegistryHolder> installRegistryHolder(jsi::Runtime *runtime) {
  auto& rt = *runtime;
  
  auto runtimeDeallocationMarker = std::make_shared<RuntimeDeallocationMarker>();
  rt
    .global()
    .setProperty(
                 rt,
                 "__RuntimeDeallocationMarker",
                 jsi::Object::createFromHostObject(rt, runtimeDeallocationMarker)
                 );
  
  return runtimeDeallocationMarker->receiveHolderReference();
}

std::shared_ptr<SharedUIRegistryHostObject> installSharedUIRegistryHostObject(jsi::Runtime *runtime) {
  auto& rt = *runtime;
  
  auto sharedUIRegistryHostObject = std::make_shared<SharedUIRegistryHostObject>();

  rt
    .global()
    .setProperty(
                 rt,
                 "SharedUIRegistry",
                 jsi::Object::createFromHostObject(rt, sharedUIRegistryHostObject)
                 );

  return sharedUIRegistryHostObject;
}

}
