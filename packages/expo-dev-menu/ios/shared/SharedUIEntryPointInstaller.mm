
#import "SharedUIEntryPointInstaller.h"
#import <React/RCTBridge+Private.h>
#import <jsi/jsi.h>
#import "common/JSIInstaller.h"

@interface SharedUIEntryPointInstaller ()

@property std::weak_ptr<shared::RegistryHolder> registryHolderRef;
@property std::shared_ptr<shared::SharedUIRegistryHostObject> sharedUIRegistryHostObject;

@end

@implementation SharedUIEntryPointInstaller

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup {
  return TRUE;
}

- (instancetype) init {
  return [super init];
}

- (void)setBridge:(RCTBridge *)bridge {
  [super setBridge:bridge];
  
  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)bridge;
  if (cxxBridge == nil) {
    return;
  }
  
  auto jsiRuntime = (facebook::jsi::Runtime *)cxxBridge.runtime;
  if (jsiRuntime == nil) {
    return;
  }
  
  auto registryHolder = shared::installRegistryHolder(jsiRuntime);
  shared::installSharedUIEntryPoint(jsiRuntime, registryHolder);
  _sharedUIRegistryHostObject = shared::installSharedUIRegistryHostObject(jsiRuntime);
  
  _registryHolderRef = registryHolder;
 }

- (NSArray<NSString *> *)supportedEvents {
  return @[];
}

- (unsigned long long)getRegistryHolder {
  return (unsigned long long)&_registryHolderRef;
}

- (void)setBoundedRegistryHolder:(unsigned long long)rawPointer {
  _sharedUIRegistryHostObject->setRegistyHolderRef(rawPointer);
}
@end
