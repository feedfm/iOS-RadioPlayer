//
//  FMRemainingTimeLabel.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 6/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"


/**
 
 Label that updates its `text` property to reflect the
 amount of time remaining to be played for the current song or,
 when no song is being played, a custom string.
 
 The label displays the elapsed time in the format '-0:00'.
 
 When no song is playing, the label will set `text` to the value
 of `textForNoTime`.
 
 */

//NOT_IB_DESIGNABLE
@interface FMRemainingTimeLabel : UILabel

/**
 The string that should be displayed when no song is being played.
 */

@property (strong, nonatomic) IBInspectable NSString *textForNoTime;

@end
