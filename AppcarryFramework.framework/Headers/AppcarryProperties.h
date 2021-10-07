//
//  AppcarryProperties.h
//  AppcarryFramework
//
//  Created by Mintu Giri on 18/07/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AppcarryProperties : NSObject

@property(nonatomic) BOOL hasPreferences;
@property(nonatomic) BOOL isFirstLaunch;
@property(nonatomic) BOOL onReceivedCalled;
@property(nonatomic, nullable) NSString * referrer;
@property(nonatomic, nullable) NSMutableDictionary<NSString *, id> * propertiesMap;
@property(nonatomic, nullable) NSUserDefaults * preference;

+(instancetype) getInstance;

-(NSUserDefaults *) getPreferences;

-(void) set: (NSString *) propertyName : (id) propertyValue;

-(id) get: (NSString *) propertyName;

-(void) remove: (NSString *) propertyName;

-(NSString *) getString: (NSString *) propertyName;

-(void) setReferrer: (NSString * _Nullable) referrer;

-(NSString *) getReferrer;

-(void) setCustomData: (NSString *) propertyCustomData;

-(void) setUserEmails: (NSString *) userEmail;

-(void) saveProperties;

-(void) loadProperties;

@end

NS_ASSUME_NONNULL_END
