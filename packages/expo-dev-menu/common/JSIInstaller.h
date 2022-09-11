#pragma once
#ifdef __cplusplus

#include "RegistryHolder.h"
#include "SharedUIRegistryHostObject.h"

#include <jsi/jsi.h>
#include <memory>

namespace jsi = facebook::jsi;

namespace shared {
void installSharedUIEntryPoint(jsi::Runtime *runtime, std::weak_ptr<RegistryHolder> registryHolder);

std::weak_ptr<RegistryHolder> installRegistryHolder(jsi::Runtime *runtime);

std::shared_ptr<SharedUIRegistryHostObject> installSharedUIRegistryHostObject(jsi::Runtime *runtime);
}

#endif // __cplusplus
