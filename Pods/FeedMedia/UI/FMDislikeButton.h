//
//  FMDislikeButton.h
//  iOS-UI-SDK
//
//  This class extends UIButton so that, when clicked, it asks the
//  Feed Media player to dislike to the current song. When the current
//  song is disliked (either from user input now or the server tells us
//  that the song was disliked in the past), the button is put in a
//  'selected' state. When there is no song currently being played
//  this button is disabled.
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 
 Button that automatically changes its `enabled` and `selected`
 properties based on the state of the music player, and sends `dislike` and
 `unlike` requests to the music player when tapped.
 
 To properly render a 'dislike' button, the following images should be assigned to
 the following states:
 
 - when `enabled = false`, the button should render as disabled
 - when `enabled = true` and `selected = true`, the button should render to indicate
   the user *dislikes* the current song
 - when `enabled = true` and `selected = false`, the button should render to indicate
   the user has *not disliked* the current song
 
 When a user taps on the button while it is enabled and selected, the button will call
 `[FMAudioPlayer unlike]`. When a user taps on the button while it is enabled and not
 selected, the button will call `[FMAudioPlayer dislike]`.
 
 The button will listen for state change events from the `FMAudioPlayer` and update its
 state accordingly.
 
 */

//NOT_IB_DESIGNABLE
@interface FMDislikeButton : UIButton

@end
