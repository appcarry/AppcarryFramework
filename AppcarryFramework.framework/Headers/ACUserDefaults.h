//
//  ACUserDefaults.h
//  AppcarryFramework
//
//  Created by Mintu Giri on 26/08/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACUserDefaults : NSObject

+(void) saveData:(id) value : (NSString *) key;

+(void) saveIntData:(int) value : (NSString *) key;

+(NSInteger) getIntData:(NSString *) key;

+(void) removeData:(NSString *) key;

+(id) getData:(NSString *) key;

+(BOOL) isKeyExists : (NSString *) key;

@end

NS_ASSUME_NONNULL_END
