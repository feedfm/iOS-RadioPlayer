//
//  FeedMediaCore.h
//  FeedMediaCore
//
//  Created by Eric Lambrecht on 9/6/17.
//  Copyright © 2017 Feed Media. All rights reserved.
//

#define FEED_MEDIA_CLIENT_VERSION @"4.2.2"

// All public headers
#import "FMAudioItem.h"
#import "FMAudioPlayer.h"
#import "FMLockScreenDelegate.h"
#import "FMError.h"
#import "FMLog.h"
#import "FMStation.h"
#import "FMStationArray.h"

#if TARGET_OS_TV
#else
#import "CWStatusBarNotification.h"
#endif
