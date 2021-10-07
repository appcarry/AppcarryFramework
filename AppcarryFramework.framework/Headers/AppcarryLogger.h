//
//  AppcarryLogger.h
//  AppcarryFramework
//
//  Created by Mintu Giri on 19/07/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AppcarryLogger : NSObject

#define AC_DEBUG @"APPCARRY_DEBUG: "
#define AC_INFO @"APPCARRY_INFO: "
#define AC_ERROR @"APPCARRY_ERROR: "
#define AC_VERBOSE @"APPCARRY_VERBOSE: "
#define AC_WARNING @"APPCARRY_WARNING: "

+(instancetype) getInstance;

-(void) debug: (id) logMessage;
-(void) info: (id) logMessage;
-(void) error: (id) logMessage;
-(void) verbose: (id) logMessage;
-(void) warning: (id) logMessage;

@end

NS_ASSUME_NONNULL_END
