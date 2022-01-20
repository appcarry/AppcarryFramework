# Appcarry iOS SDK integration

# Overview

> Appcarry iOS SDK provides app install and event recording functionality to iOS apps. The SDK can be used with ObjC/Swift.

---

# Install SDK

> Learn how to download and install the iOS SDK.

---

## Before you begin

> You need [Xcode](https://developer.apple.com/xcode/resources) to follow along with these guides.

---

## Download and install the SDK

### Install using CocoaPods

##### Download CocoaPods
---

> [Download and install](https://guides.cocoapods.org/using/getting-started.html#installation) the latest version of CocoaPods.

##### Add dependencies
---

> Add the [latest version of AppcarryFramework](https://github.com/appcarry/AppcarryFramework/releases) to your project's Podfile:

```objectivec
pod 'AppcarryFramework', '1.1.3'
pod 'Firebase/Messaging'
```

##### Install dependencies
---

> In your terminal, navigate to your project's root folder and run **pod install**.

##### Open Xcode workspace
---

> In Xcode, use the **.xcworkspace** file to open the project from this point forward, instead of the **.xcodeproj** file.

> If you are developing a tvOS app, CocoaPods automatically adds the relevant dependencies from **AppcarryFramework**.

# Integrate SDK

Learn how to initialize and start the iOS SDK.

### Initializing the iOS SDK

##### 1. **Import dependencies**
---

> Import AppcarryFramework and add AppcarryDelegate to AppDelegate:

* Objective C

```objectivec
// AppDelegate.h
@import FirebaseMessaging;
@import AppcarryFramework;

@interface AppDelegate : UIResponder <UIApplicationDelegate, AppcarryDelegate>

@end
```

* Swift

```swift
import UIKit
import FirebaseMessaging
import AppcarryFramework

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, AppcarryDelegate {
    // ...
}
```

##### 2. **Initialize the SDK**
---

> In **didFinishLaunchingWithOptions** configure your Apple App ID and Appcarry dev key:

* Objective C

```objectivec
[Appcarry getInstance].appcarryDevKey = @"Your Dev Key";
[Appcarry getInstance].appleAppID = @"Your Apple ID";
```

* Swift

```swift
Appcarry.getInstance().appcarryDevKey = "Your Dev Key"
Appcarry.getInstance().appleAppID = "Your Apple ID"
```

## Starting the iOS SDK

> In applicationDidBecomeActive, call **start**:

* Objective C

```objectivec
[[Appcarry getInstance] start];
```

* Swift

```swift
func applicationDidBecomeActive(_ application: UIApplication) {
    Appcarry.getInstance().start()
}
```

> In applicationDidEnterBackground, call **startBackground**:

* Objective C

```objectivec
[[Appcarry getInstance] startBackground];
```

* Swift

```swift
func applicationDidEnterBackground(_ application: UIApplication) {
    Appcarry.getInstance().startBackground()
}
```

## Add SceneDelegate support

**optional**

> Do the following only if you use **SceneDelegates**:

In **didFinishLaunchingWithOptions**, add a **UIApplicationDidBecomeActiveNotification** & **didEnterBackgroundNotification** observer and set it to run start:

* Objective C

```objectivec
@implementation AppDelegate
// SceneDelegate support - start Appcarry SDK
- (void)sendLaunch:(UIApplication *)application {
    [appcarry start];
}
- (void)sendBackground:(UIApplication *)application {
    [appcarry startBackground];
}
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // ...
    // SceneDelegate support
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(sendLaunch:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(sendBackground:)
                                                 name:UIApplicationDidEnterBackgroundNotification
                                               object:nil];

    if (@available(iOS 10, *)) {
            UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
            center.delegate = self;
            [center requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error) {
            }];
        }else {
            UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes: UIUserNotificationTypeAlert | UIUserNotificationTypeSound | UIUserNotificationTypeBadge categories:nil];
            [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
        }

        [[UIApplication sharedApplication] registerForRemoteNotifications];
    // ...
    return YES;
}
// ...
@end

```

* Swift

```swift
import UIKit
import AppcarryFramework

@main
class AppDelegate: UIResponder, UIApplicationDelegate, AppcarryDelegate {
        
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        NotificationCenter.default.addObserver(self, selector: NSSelectorFromString("sendLaunch"), name:UIApplication.didBecomeActiveNotification, object: nil)
        NotificationCenter.default.addObserver(self, selector: NSSelectorFromString("sendBackground"), name:UIApplication.didEnterBackgroundNotification, object: nil)
        
        return true
    }
    
    @objc func sendLaunch() {
        Appcarry.getInstance().start()
    }

    @objc func sendBackground() {
        Appcarry.getInstance().startBackground()
    }
```

## Full example

* Objective C

```objectivec
#import "AppDelegate.h"
@import FirebaseMessaging;
@import AppcarryFramework;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)sendLaunch:(UIApplication *)application {
    [[Appcarry getInstance] start];
}
- (void)sendBackground:(UIApplication *)application {
    [[Appcarry getInstance] startBackground];
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [Appcarry getInstance].appcarryDevKey = @"appcarry123";
    [Appcarry getInstance].appleAppID = @"appcarryAppId123";
    // Must be called AFTER setting appcarryDevKey and appleAppID
    [Appcarry getInstance].delegate = self;
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(sendLaunch:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(sendBackground:)
                                                 name:UIApplicationDidEnterBackgroundNotification
                                               object:nil];
    // SceneDelegate support
    if (@available(iOS 10, *)) {
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        center.delegate = self;
        [center requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error) {
        }];
    }else {
        UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes: UIUserNotificationTypeAlert | UIUserNotificationTypeSound | UIUserNotificationTypeBadge categories:nil];
        [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
    }
    
    [[UIApplication sharedApplication] registerForRemoteNotifications];
    
    return YES;
}

- (void)onConversionDataFail:(nonnull NSString *)error {
    
}

- (void)onConversionDataSuccess:(nonnull NSDictionary *)conversionInfo {
}

@end
```

* Swift

```swift
import UIKit
import AppcarryFramework

@main
class AppDelegate: UIResponder, UIApplicationDelegate, AppcarryDelegate {
    
    func onConversionDataSuccess(_ conversionInfo: [AnyHashable : Any]) {
            print(conversionInfo)
    }
    
    func onConversionDataFail(_ error: String) {
            print(error)
    }
        
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.

        Appcarry.getInstance().appcarryDevKey = "Your Dev Key"
        Appcarry.getInstance().appleAppID = "Your Apple ID"
        Appcarry.getInstance().delegate = self

        NotificationCenter.default.addObserver(self, selector: NSSelectorFromString("sendLaunch"), name:UIApplication.didBecomeActiveNotification, object: nil)
        NotificationCenter.default.addObserver(self, selector: NSSelectorFromString("sendBackground"), name:UIApplication.didEnterBackgroundNotification, object: nil)
        
        return true
    }
    
    @objc func sendLaunch() {
        Appcarry.getInstance().start()
    }

    @objc func sendBackground() {
        Appcarry.getInstance().startBackground()
    }
}
```

## Enabling App Tracking Transparency (ATT) support

#### Call **requestTrackingAuthorization** where you wish to display the prompt: 

> Call requestTrackingAuthorization

* Objective C

```objectivec
 (void)viewDidLoad {
    [super viewDidLoad];
    
    if @available(iOS 14, *) {
      [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
        NSLog(@"Status: %lu", (unsigned long)status);
      }];
    }
}
```

* Swift

```swift
override func viewDidLoad() {
  super.viewDidLoad()
  
  if #available(iOS 14, *) {
    ATTrackingManager.requestTrackingAuthorization { (status) in }
  }
}
```

#### Customizing the ATT consent dialog

> The ATT consent dialog can be customized by modifying your Xcode project's info.plist:

![N|Solid](https://files.readme.io/811c80f-infoplist-att.png)

----

# License


Appcarry.com

