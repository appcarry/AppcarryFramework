//
//  Appcarry.h
//  AppcarryFramework
//
//  Created by Mintu Giri on 18/07/21.
//

#import <Foundation/Foundation.h>
#import <AppcarryFramework/AppcarryLogger.h>
#import <UIKit/UIKit.h>
#import <AdSupport/AdSupport.h>
#import <CoreLocation/CoreLocation.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <AppcarryFramework/PlatformIdentifier.h>
#import <AppcarryFramework/AppcarryProperties.h>
#import <AppcarryFramework/ACUserDefaults.h>
#import "KeychainItemWrapper.h"
#import <BackgroundTasks/BackgroundTasks.h>
#import "Reachability.h"
#import <sys/utsname.h>


@import FirebaseMessaging;



NS_ASSUME_NONNULL_BEGIN

@protocol AppcarryDelegate <NSObject>

-(void) onConversionDataSuccess:(NSDictionary *)conversionInfo;

-(void) onConversionDataFail:(NSString *)error;

@optional

-(void) onAppOpenAttribution:(NSDictionary *) attributionData;

-(void) onAppOpenAttributionFailure:(NSString *) error;

-(NSDictionary <NSString *, NSString *> * _Nullable) allHTTPHeaderFieldsForResolveDeepLinkURL:(NSURL *) URL;

@end

//Enums
typedef enum  {
    /// None
    EmailCryptTypeNone = 0,
    /// SHA1
    EmailCryptTypeSHA1 = 1,
    /// MD5
    EmailCryptTypeMD5 = 2,
    /// SHA256
    EmailCryptTypeSHA256 = 3
} EmailCryptType;


@interface Appcarry : NSObject

//Properties
@property(nonatomic, strong) NSString * appcarryDevKey;
@property(nonatomic, strong) NSString * attributionID;
@property(nonatomic, strong) NSString * appleAppID;
@property(nonatomic, strong) NSString * webHookUrl;
@property(nonatomic, strong) NSString * fcmToken;
@property(nonatomic) BOOL disableAdvertisingIdentifier;
@property(nonatomic, strong, nullable) NSString * customerUserID;
@property(nonatomic) BOOL shouldCollectDeviceName;
@property(nonatomic, strong, nullable, setter = setAppInviteLinkTrack:) NSString * appInviteLinkTrackID;
@property(atomic) BOOL anonymizeUser;
@property(nonatomic, nullable) NSArray<NSString *> * resolveDeepLinkURLs;
@property(nonatomic, nullable) NSArray<NSString *> * linkTrackCustomDomains;
@property(nonatomic, strong, readonly) NSString * host;
@property(nonatomic, strong, readonly) NSString * hostPrefix;
@property(atomic) NSUInteger minTimeBetweenSessions;
@property(atomic) BOOL isStopped;
@property(nonatomic, nullable) NSURL *facebookDeferredAppLink;
@property(nonatomic, nullable) NSArray<NSString *> * sharingFilter;
@property(nonatomic) NSUInteger deepLinkTimeout;
@property(nonatomic, strong, readonly) NSString * advertisingIdentifier;
@property(nonatomic, strong, nullable, setter = setAdditionalData:) NSDictionary * customData;
@property(nonatomic) BOOL disableSKAdNetwork;
@property(nonatomic, strong, nullable) NSString * currencyCode;
@property(nonatomic) BOOL isDebug;

@property(weak, nonatomic) id<AppcarryDelegate> delegate;
//@property(weak, nonatomic) id<AppsFlyerDeepLinkDelegate> deepLinkDelegate;

@property(nonatomic) BOOL useReceiptValidationSandbox;
@property(nonatomic) BOOL useUninstallSandbox;
@property(nonatomic, nullable) NSString * phoneNumber;
@property(nonatomic) BOOL disableIDFVCollection;


//Functions
+(instancetype) getInstance;

-(void) stop:(bool) stopFlag;

-(NSString *) getSdkVersion;

-(void) updateServerUninstallToken:(NSString *) uninstallToken;

-(NSString *) phoneNumber UNAVAILABLE_ATTRIBUTE;

-(void) waitForATTUserAuthorizationWithTimeoutInterval:(NSTimeInterval) timeoutInterval
NS_SWIFT_NAME(waitForATTUserAuthorization(timeoutInterval:));

-(void) enableFacebookDeferredApplinksWithClass:(Class _Nullable) facebookAppLinkUtilityClass;

-(void) setUserEmails:(NSArray<NSString *> * _Nullable) userEmails withCryptType: (EmailCryptType) type;

-(void) start;

//-(void) startWithCompletionHandler:(void (^ _Nullable)(NSDictionary<NSString *, id> * _Nullable dictionary, NSError * _Nullable error)) completionHandler;

-(void) logEvent:(NSString *) eventName withValues:(NSDictionary * _Nullable) values;

//-(void) logEventWithEventName:(NSString *) eventName
//                  eventValues:(NSDictionary<NSString * , id> * _Nullable) eventValues
//            completionHandler:(void (^ _Nullable)(NSDictionary<NSString *, id> * _Nullable dictionary, NSError * _Nullable error)) completionHandler
//NS_SWIFT_NAME(logEvent(name:values:completionHandler:));

-(void) validateAndLogInAppPurchase:(NSString * _Nullable) productIdentifier
                              price:(NSString * _Nullable) price
                           currency:(NSString * _Nullable) currency
                      transactionId:(NSString * _Nullable) transactionId
               additionalParameters:(NSDictionary * _Nullable) params
                            success:(void (^ _Nullable)(NSDictionary * response)) successBlock
                            failure:(void (^ _Nullable)(NSError * _Nullable error, id _Nullable reponse)) failedBlock NS_AVAILABLE(10_7, 7_0);

-(void) logLocation:(double) longitude latitude:(double) latitude NS_SWIFT_NAME(logLocation(longitude:latitude:));

-(NSString *) getAppcarryUID;

-(NSString *) getAttributionID;

-(void) handleOpenURL:(NSURL * _Nullable) url sourceApplication:(NSString * _Nullable) sourceApplication API_UNAVAILABLE(macos);

-(void) handleOpenURL:(NSURL * _Nullable) url
    sourceApplication:(NSString * _Nullable) sourceApplication
       withAnnotation:(id _Nullable) annotation API_UNAVAILABLE(macos);

-(void) handleOpenUrl:(NSURL * _Nullable) url options:(NSDictionary * _Nullable) options API_UNAVAILABLE(macos);

-(BOOL) continueUserActivity:(NSUserActivity * _Nullable) userActivity
          restorationHandler:(void (^ _Nullable)(NSArray * _Nullable)) restorationHandler NS_AVAILABLE_IOS(9_0) API_UNAVAILABLE(macos);

-(void) handlePushNotification:(NSDictionary * _Nullable) pushPayload;

-(void) registerUninstall:(NSData * _Nullable) deviceToken;

-(void) remoteDebuggingCallWithData:(NSString *) data;

-(void) performOnAppAttributionWithURL:(NSURL * _Nullable) url;

-(void) setHost:(NSString *)host withHostPrefix:(NSString *) hostPrefix;

-(void) setSharingFilterForAllPartners;

-(void) appendParametersToDeepLinkingURLWithString:(NSString *) containsString
                                        parameters:(NSDictionary<NSString *, NSString*> *) parameters
NS_SWIFT_NAME(appendParametersToDeeplinkURL(contains:parameters:));

-(void) addPushNotificationDeepLinkPath:(NSArray<NSString *> *) deepLinkPath;

-(void) setPartnerDataWithPartnerId:(NSString * _Nullable)partnerId partnerInfo:(NSDictionary<NSString *, id> * _Nullable) partnerInfo
NS_SWIFT_NAME(setPartnerData(partnerId:partnerInfo:));

-(void) startBackground;

@end

NS_ASSUME_NONNULL_END
