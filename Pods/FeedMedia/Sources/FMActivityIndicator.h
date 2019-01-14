//
//  FMActivityIndicator.h
//  iOS-UI-SDK
//
//  This class extends UIActivityIndicator to watch the state of
//  the Feed Media player. When the player is in a state such
//  that it is waiting for a network response before it can continue
//  play music, this indicator will begin animating.
//
//  You can enable the 'hidesWhenNotAnimating' so that
//  the indicator is only visible when the player is actively waiting
//  for something. If an FMPlayPauseButton is in the same location
//  on the screen and has its 'hideWhenStalled' property set to true,
//  then only the play/pause button or the indicator will be visible
//  at the same time.
//
//  Created by Eric Lambrecht on 3/11/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"


/**
 
 Indicator view that starts animation automatically
 whenever the player is stalled, waiting for a song from the server, or 
 asking the server for permission to skip the current song. The animation
 is stopped in all other states.
 
 */

//NOT_IB_DESIGNABLE
@interface FMActivityIndicator : UIActivityIndicatorView

@end
