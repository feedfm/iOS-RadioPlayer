//
//  FMSkipButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 This button automatically updates its `enabled` property to reflect whether
 the currently playing song (if any) can be skipped, and responds to taps by
 requesting that the current song be skipped. 
 
 If there is a playing or paused song that can be skipped and a skip request
 is not currently in progress, then `enabled` is set to `true`, and `false` otherwise.

 */

//NOT_IB_DESIGNABLE
@interface FMSkipButton : UIButton


@end
