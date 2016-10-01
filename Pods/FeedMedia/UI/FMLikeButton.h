//
//  FMLikeButton.h
//  iOS-UI-SDK
//
//  This class extends UIButton so that, when clicked, it asks the
//  Feed Media player to like to the current song. When the current
//  song is liked (either from user input now or the server tells us
//  that the song was liked in the past), the button is put in a
//  'selected' state. When there is no song currently being played
//  this button is disabled.
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 
 Button that automatically changes its `enabled` and `selected`
 properties based on the state of the music player, and sends `like` and
 `unlike` requests to the music player when tapped.
 
 To properly render a 'like' button, the following images should be assigned to
 the following states:
 
 - when `enabled = false`, the button should render as disabled
 - when `enabled = true` and `selected = true`, the button should render to indicate
 the user *likes* the current song
 - when `enabled = true` and `selected = false`, the button should render to indicate
 the user has *not liked* the current song
 
 When a user taps on the button while it is enabled and selected, the button will call
 `[FMAudioPlayer unlike]`. When a user taps on the button while it is enabled and not
 selected, the button will call `[FMAudioPlayer like]`.
 
 The button will listen for state change events from the `FMAudioPlayer` and update its
 state accordingly.
 
 */

//NOT_IB_DESIGNABLE
@interface FMLikeButton : UIButton

@end
