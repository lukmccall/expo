#import <React/RCTBridgeModule.h>
#import <React/RCTBridgeDelegate.h>
#import <React/RCTEventEmitter.h>


@interface SharedUIEntryPointInstaller : RCTEventEmitter <RCTBridgeModule>

- (unsigned long long)getRegistryHolder;

- (void)setBoundedRegistryHolder:(unsigned long long)rawPointer;

@end
