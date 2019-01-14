//
//  FMElapsedTimeLabel.h
//  iOS-UI-SDK
//
//  This class extends UILabel to automatically set its
//  text to be the elapsed time of the currently playing
//  song (and it is updated every .5 second), or the
//  value of the textForNoTime property when
//  no song is playing. The setText: call is stubbed out
//  so that the text cannot be changed by the client.
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 Label that updates its `text` property to reflect the
 amount of time that has elapsed since the start of the current song or,
 when no song is being played, a custom string.
 
 The label displays the elapsed time in the format '0:00'.
 
 When no song is playing, the label will set `text` to the value
 of `textFoNoTime`.
 
 */

//NOT_IB_DESIGNABLE
@interface FMElapsedTimeLabel : UILabel

/**
 The string that should be displayed when no song is being played.
 */

@property (strong, nonatomic) IBInspectable NSString *textForNoTime;

@end
