// Copyright © 2021-present 650 Industries, Inc. (aka Expo)

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <memory>

#include "common/JSIInstaller.h"

namespace jni = facebook::jni;
namespace jsi = facebook::jsi;

namespace shared {

class SharedUIEntryPointInstaller : public jni::HybridClass<SharedUIEntryPointInstaller> {
public:
  static auto constexpr
    kJavaDescriptor = "Lexpo/modules/devmenu/shared/SharedUIEntryPointInstaller;";
  static auto constexpr TAG = "SharedUIEntryPointInstaller";

  static jni::local_ref<jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis);

  static void registerNatives();

  void install(jlong jsRuntimePointer);

  unsigned long long getRegistryHolder();

  void setBoundedRegistryHolder(unsigned long long rawPointer);

private:
  friend HybridBase;
  jni::global_ref<SharedUIEntryPointInstaller::javaobject> javaPart_;

  explicit SharedUIEntryPointInstaller(jni::alias_ref<jhybridobject> jThis);

  std::weak_ptr<shared::RegistryHolder> registryHolderRef;
  std::shared_ptr<shared::SharedUIRegistryHostObject> sharedUIRegistryHostObject;


};
} // namespace expo
