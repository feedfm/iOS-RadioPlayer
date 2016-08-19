//
//  FMPlayPauseButton.h
//  UITests
//
//  This class extends UIButton so that, when clicked, it asks the
//  Feed Media player to either start playing music, resume the
//  currently paused song, or pause the currently playing song.
//
//  When the button is not selected, it should indicate that a click
//  will start music playback (so you would display the text 'play'
//  or the triangular 'play' icon), and when the button is selected
//  it means we are currently playing music and a click will pause
//  music playback.
//
//  If the 'hideWhenStalled' boolean is set to YES, then this
//  button will hide itself from display. Presumably you have a
//  FMActivityIndicator in the same location as the button that will
//  then appear to indicate that the player is waiting for
//  data from the network to continue.
//
//  Created by Eric Lambrecht on 3/6/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

//NOT_IB_DESIGNABLE
@interface FMPlayPauseButton : UIButton

@property (nonatomic) IBInspectable BOOL hideWhenStalled;

@end
