//
//  PlatformIdentifier.h
//  AppcarryFramework
//
//  Created by Mintu Giri on 17/08/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PlatformIdentifier : NSObject

+(instancetype) getInstance;

-(NSString *) getPlatformExtension;

-(bool) doesClassExist: (NSString *) bundleName;

@end

NS_ASSUME_NONNULL_END
