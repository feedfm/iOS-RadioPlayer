//
//  FMPlayPauseButton.h
//  UITests
//
//
//  Created by Eric Lambrecht on 3/6/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 Button that automatically updates its `selected` property to reflect 
 whether or not music is currently playing, and responds to touches by
 calling `[FMAudioPlayer play]` or `[FMAudioPlayer pause]`.

 When the button has `selected = false`, it should render an image to
 indicate that tapping the button will start music (a triangle 'play'
 image). When the button has
 `selected = true` it should indicate that tapping the button will
 pause music playback (a 'pause' image).

 If the `hideWhenStalled` property is set to `YES`, then this button
 will set its `hidden` property to true when the player is stalled
 waiting for audio data over the network. Presumably there is an
 `FMActivityIndicator` in the same location on the screen that becomes
 visible at the same time and the user gets an indication that the
 player is working, despite no music playing.

 If the `station` property is set (directly, or via `stationName`), 
 then the button's visibility and `selected` state are dependent 
 on the active station matching this value. Similarly, if the `audioItem`
 property is set, the button's visibility and `selected` state
 are dependent on the active song matching this value.
 
 When the active station does not match the button's `station` value,
 the button will have `selected = false` and will be visible. Tapping
 the button will cause the active station to change to the `station` 
 value and playback will be started in that station.
 
 When the active song does not match the button's `audioItem` value,
 the butotn will have `selected = false` and will be visible. Tapping
 the button will cause the player to switch to the `audioItem`s station
 and request playback of that specific song.
 
 When the active station does match the button's `stationName` or
 `station` value, the button's `selected` property will be adjusted
 as above. Additionally, if `hideWhenActive` is true and the active
 station matches, the button will be hidden.
 
 Similarly, if the active song does match the button's `audioItem`
 value, the button's `selected` property will be adjusted
 as above. Additionally, if `hideWhenActive` is true and the active
 song matches, the button will be hidden.

 */
 

//NOT_IB_DESIGNABLE
@interface FMPlayPauseButton : UIButton


/**
 When set, the button looks for a station with the given
 name, and sets the `station` property to that station. This property
 is optional and is primarily offered to assign a button to
 a station via Interface Builder.
 */

@property (nonatomic, strong) IBInspectable NSString *stationName;

/**
 If this property is set, then the button only controls playback for
 the given station and the button's `selected` status is only set when
 the active station matches this value. 
 
 When the button is tapped, but the active station does not match this 
 value, the button makes this station the active station and starts 
 playback. If the active station already matches this button, then a 
 tap causes playback to pause.
 
 Assigning a non-nil value to this property causes `audioItem` to
 be set to nil.
 */

@property (nonatomic, strong) FMStation *station;

/**
 If this property is set, then the button only controls playback for
 the given song and the button's `selected` status is only set when
 the active song matches this value.
 
 When the button is tapped, but the active song does not match this
 value, the button makes this song's station  the active station and 
 then tries to start playback of the requested song. If the active song
 already matches this button, then a tap causes playback to pause.
 
 Assigning a non-nil value to this property causes `station` to
 be set to nil.
 */

@property (nonatomic, strong) FMAudioItem *audioItem;


/**
 
 If true, this button will set its `hidden` property to `true` when
 the `FMAudioPlayer` is stalled, and `false` otherwise.
 
 If the `station` or `audioItem` property is set, then the button 
 will only hide when the active station or song matches that property
 and the player is stalled.
 */

@property (nonatomic) IBInspectable BOOL hideWhenStalled;


/**
 When true, this button will hide itself when it matches the active
 station or audioItem and the player is not in the idle state.
 */

@property (nonatomic) IBInspectable BOOL hideWhenActive;

/**
 When true, and if the player is already playing music in a station
 that doesn't match this button's `station` property,
 the transition to playback of this station will be crossfaded.
 
 This currently does not apply similarly to the 'audioItem'
 property, but may in a future update.
 **/

@property (nonatomic) IBInspectable BOOL crossfade;


@end
