//
//  FMTotalTimeLabel.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 This label automatically sets its `text` value to represent the
 total playback time of the current song. If the `textForNoTime`
 property is set, then `text` is set to that value when there is
 no currently playing or paused song.
 
 */

//NOT_IB_DESIGNABLE
@interface FMTotalTimeLabel : UILabel

/**
 
 If set, this label will set its `text` property to this value
 when no song is playing or paused.
 
 */

@property (strong, nonatomic) IBInspectable NSString *textForNoTime;

@end
