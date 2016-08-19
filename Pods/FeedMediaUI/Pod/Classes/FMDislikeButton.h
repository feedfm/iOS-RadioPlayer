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

//NOT_IB_DESIGNABLE
@interface FMDislikeButton : UIButton

@end
