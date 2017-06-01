//
//  FMStationButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 5/14/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 
 This button sets its `selected` property to true if
 the current active station matches this buttons `stationName`
 property. This button will change the active station
 to the one with the same name as `stationName` when tapped, 
 and optionally start music playback in that station if the
 `playOnClick` property is true.
 
 When `selected` is `true`, this button should render as a
 *play* button, and when it is `false`, it should render as
 *now playing* or *active*.
 
 */

//NOT_IB_DESIGNABLE
@interface FMStationButton : UIButton

/**
 This should be the exact name of a station that this
 button represents.
 */

@property (nonatomic, strong) IBInspectable NSString *stationName;

/**
 This represents the station that this button represents. Only this
 or stationName should be used - not both.
 */

@property (nonatomic, strong) FMStation *station;

/**
 When true, the button will call `[FMAudioPlayer play]` after
 changing the station after a tap.
 */

@property (nonatomic) IBInspectable BOOL playOnClick;

/**
 When true, this button will hide itself when it matches the active
 station and the player is not in the idle state.
 */

@property (nonatomic) IBInspectable BOOL hideWhenActive;

@end
