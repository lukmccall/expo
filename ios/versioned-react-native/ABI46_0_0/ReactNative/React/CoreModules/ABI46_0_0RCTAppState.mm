/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI46_0_0RCTAppState.h"

#import <ABI46_0_0FBReactNativeSpec/ABI46_0_0FBReactNativeSpec.h>
#import <ABI46_0_0React/ABI46_0_0RCTAssert.h>
#import <ABI46_0_0React/ABI46_0_0RCTBridge.h>
#import <ABI46_0_0React/ABI46_0_0RCTEventDispatcherProtocol.h>
#import <ABI46_0_0React/ABI46_0_0RCTUtils.h>

#import "ABI46_0_0CoreModulesPlugins.h"

static NSString *ABI46_0_0RCTCurrentAppState()
{
  static NSDictionary *states;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    states = @{@(UIApplicationStateActive) : @"active", @(UIApplicationStateBackground) : @"background"};
  });

  if (ABI46_0_0RCTRunningInAppExtension()) {
    return @"extension";
  }

  return states[@(ABI46_0_0RCTSharedApplication().applicationState)] ?: @"unknown";
}

@interface ABI46_0_0RCTAppState () <ABI46_0_0NativeAppStateSpec>
@end

@implementation ABI46_0_0RCTAppState {
  NSString *_lastKnownState;
}

ABI46_0_0RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup
{
  return YES;
}

- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

- (ABI46_0_0facebook::ABI46_0_0React::ModuleConstants<ABI46_0_0JS::NativeAppState::Constants>)constantsToExport
{
  return (ABI46_0_0facebook::ABI46_0_0React::ModuleConstants<ABI46_0_0JS::NativeAppState::Constants>)[self getConstants];
}

- (ABI46_0_0facebook::ABI46_0_0React::ModuleConstants<ABI46_0_0JS::NativeAppState::Constants>)getConstants
{
  __block ABI46_0_0facebook::ABI46_0_0React::ModuleConstants<ABI46_0_0JS::NativeAppState::Constants> constants;
  ABI46_0_0RCTUnsafeExecuteOnMainQueueSync(^{
    constants = ABI46_0_0facebook::ABI46_0_0React::typedConstants<ABI46_0_0JS::NativeAppState::Constants>({
        .initialAppState = ABI46_0_0RCTCurrentAppState(),
    });
  });

  return constants;
}

#pragma mark - Lifecycle

- (NSArray<NSString *> *)supportedEvents
{
  return @[ @"appStateDidChange", @"memoryWarning" ];
}

- (void)startObserving
{
  for (NSString *name in @[
         UIApplicationDidBecomeActiveNotification,
         UIApplicationDidEnterBackgroundNotification,
         UIApplicationDidFinishLaunchingNotification,
         UIApplicationWillResignActiveNotification,
         UIApplicationWillEnterForegroundNotification
       ]) {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleAppStateDidChange:)
                                                 name:name
                                               object:nil];
  }

  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(handleMemoryWarning)
                                               name:UIApplicationDidReceiveMemoryWarningNotification
                                             object:nil];
}

- (void)stopObserving
{
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - App Notification Methods

- (void)handleMemoryWarning
{
  if (self.bridge) {
    [self sendEventWithName:@"memoryWarning" body:nil];
  }
}

- (void)handleAppStateDidChange:(NSNotification *)notification
{
  NSString *newState;

  if ([notification.name isEqualToString:UIApplicationWillResignActiveNotification]) {
    newState = @"inactive";
  } else if ([notification.name isEqualToString:UIApplicationWillEnterForegroundNotification]) {
    newState = @"background";
  } else {
    newState = ABI46_0_0RCTCurrentAppState();
  }

  if (![newState isEqualToString:_lastKnownState]) {
    _lastKnownState = newState;
    if (self.bridge) {
      [self sendEventWithName:@"appStateDidChange" body:@{@"app_state" : _lastKnownState}];
    }
  }
}

#pragma mark - Public API

/**
 * Get the current background/foreground state of the app
 */
ABI46_0_0RCT_EXPORT_METHOD(getCurrentAppState : (ABI46_0_0RCTResponseSenderBlock)callback error : (__unused ABI46_0_0RCTResponseSenderBlock)error)
{
  callback(@[ @{@"app_state" : ABI46_0_0RCTCurrentAppState()} ]);
}

- (std::shared_ptr<ABI46_0_0facebook::ABI46_0_0React::TurboModule>)getTurboModule:
    (const ABI46_0_0facebook::ABI46_0_0React::ObjCTurboModule::InitParams &)params
{
  return std::make_shared<ABI46_0_0facebook::ABI46_0_0React::NativeAppStateSpecJSI>(params);
}

@end

Class ABI46_0_0RCTAppStateCls(void)
{
  return ABI46_0_0RCTAppState.class;
}
