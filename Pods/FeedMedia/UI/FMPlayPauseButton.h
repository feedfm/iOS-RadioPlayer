//
//  FMPlayPauseButton.h
//  UITests
//
//
//  Created by Eric Lambrecht on 3/6/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 
 Button that automatically updates its `selected` property to reflect 
 wether or not music is currently playing, and responds to touches by
 calling `[FMAudioPlayer play]` or `[FMAudioPlayer pause]`.
 
 When the button has `selected = false`, it should render an image to 
 indicate that tapping the button will start music. When the button has
 `selected = true` it should indicate that tapping the button will
 pause music playback.

 If the `hideWhenStalled` property is set to `YES`, then this button
 will set its `hidden` property to true when the player is stalled
 waiting for audio data over the network. Presumably there is an
 `FMActivityIndicator` in the same location on the screen that becomes
 visible at the same time and the user gets an indication that the
 player is working, despite no music playing.

 */
 

//NOT_IB_DESIGNABLE
@interface FMPlayPauseButton : UIButton

/**
 
 If true, this button will set its `hidden` property to `true` when
 the `FMAudioPlayer` is stalled, and `false` otherwise.
 
 */

@property (nonatomic) IBInspectable BOOL hideWhenStalled;

@end
