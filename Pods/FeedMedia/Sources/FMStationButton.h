//
//  FMStationButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 5/14/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 @deprecated The `FMPlayPauseButton` class now incorporates this functionality.
 
 This button is used to change the active station to 
 a specific station, and optionally start/pause music playback
 from that station.
 
 If you just want a button that starts or stops music, regardless
 of the active station, take a look at `FMPlayPauseButton`.
 
 Assign an `FMStation` to this button's `station` property
 or the name of a station to this button's `stationName` property.
 Now, when the button is tapped, the active station will be
 changed to this station.
 
 If the active station matches the station associated with this button
 and is additionally playing music, the button's `selected` state
 will be `true`.
 
 Depending on the other properties of this button, additional
 events may happen after a touch:
 
 if `hideWhenActive == true`, the button will be hidden when the
 active station matches this button's station
 
 if `playOnClick == true`, the button will start playback in the
 station after changing to it. If the station was already active
 and playing music, then this will pause playback of the station.
 
 */

//NOT_IB_DESIGNABLE
__attribute__ ((deprecated))
@interface FMStationButton : UIButton

/**
 This should be the exact name of a station that this
 button represents. The button will look through the list
 of available stations and set the `station` property
 to the first that matches this station name.
 */

@property (nonatomic, strong) IBInspectable NSString *stationName;

/**
 This represents the station that this button represents.
*/

@property (nonatomic, strong) FMStation *station;

/**
 When true, the button will call `[FMAudioPlayer play]` after
 changing the station after a tap. If the station was already 
 active and playing music, this will pause music playback.
 */

@property (nonatomic) IBInspectable BOOL playOnClick;

/**
 When true, this button will hide itself when it matches the active
 station and the player is not in the idle state.
 */

@property (nonatomic) IBInspectable BOOL hideWhenActive;

/**
  When true, and if the player is already playing some other station,
 the transition to playback of this station will be crossfaded.
**/

@property (nonatomic) IBInspectable BOOL crossfade;
 
 

@end
