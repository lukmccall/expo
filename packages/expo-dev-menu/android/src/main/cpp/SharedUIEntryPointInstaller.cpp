// Copyright © 2021-present 650 Industries, Inc. (aka Expo)

#include "SharedUIEntryPointInstaller.h"

#include <memory>

namespace jni = facebook::jni;
namespace jsi = facebook::jsi;

namespace shaerd {

jni::local_ref<SharedUIEntryPointInstaller::jhybriddata>
SharedUIEntryPointInstaller::initHybrid(jni::alias_ref<jhybridobject> jThis) {
  return makeCxxInstance(jThis);
}

void JSIInteropModuleRegistry::registerNatives() {
  registerHybrid({
                   makeNativeMethod("initHybrid", SharedUIEntryPointInstaller::initHybrid),
                   makeNativeMethod("install", SharedUIEntryPointInstaller::install),
                   makeNativeMethod("getRegistryHolder", SharedUIEntryPointInstaller::getRegistryHolder),
                   makeNativeMethod("setBoundedRegistryHolder", SharedUIEntryPointInstaller::setBoundedRegistryHolder)
                 })
}

SharedUIEntryPointInstaller::SharedUIEntryPointInstaller(jni::alias_ref<jhybridobject> jThis)
  : javaPart_(jni::make_global(jThis)) {}

void SharedUIEntryPointInstaller::install(jlong jsRuntimePointer) {
  auto runtime = reinterpret_cast<jsi::Runtime *>(jsRuntimePointer);

  auto registryHolder = shared::installRegistryHolder(jsiRuntime);
  shared::installSharedUIEntryPoint(jsiRuntime, registryHolder);
  sharedUIRegistryHostObject = shared::installSharedUIRegistryHostObject(jsiRuntime);

  registryHolderRef = registryHolder;
}

unsigned long long SharedUIEntryPointInstaller::getRegistryHolder() {
  return (unsigned long long)&registryHolderRef;
}

void setBoundedRegistryHolder(unsigned long long rawPointer) {
  sharedUIRegistryHostObject->setRegistyHolderRef(rawPointer);
}

} 
