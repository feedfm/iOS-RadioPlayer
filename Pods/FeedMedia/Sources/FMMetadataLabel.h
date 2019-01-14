//
//  FMMetadataLabel.h
//  iOS-UI-SDK
//
//  This label sets its 'text' property to match its 'format' propery, but with
//  the following strings replaced to reflect the currently playing song:
//
//   %ARTIST - the name of the current artist
//   %TRACK  - the name of the current track
//   %ALBUM  - the name of the current album
//
//  If no song is playing, then the text is set to the empty string.
//
//  If you set the 'text' property to anything while in Interface Builder, you'll
//  see that text rendered while designing things, but it will not appear
//  in the running app.
//
//  Created by Eric Lambrecht on 4/27/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

#if TARGET_OS_TV
#else
#import <MarqueeLabel/MarqueeLabel.h>
#endif

/**
 
 Label that displays
 text with substitutions based on the currently playing song.
 
 If no song is being played, the `text` property is set to an empty string.
 
 If a song is playing, the label will assing the value of `format` with
 some substitutions to the `text` property. The following table shows the 
 strings in the `format` property and what they are substituted with:
 
 - %ARTIST is replaced with the name of the artist on the current song
 - %ALBUM is replaced with the name of the album the current song appears on
 - %TRACK is replaced with the title of the current song
 
 For iOS, this class subclasses `MarqueeLabel` so that the field is automatically
 animated if it is too big to fully render its contents.
 
 */

#if TARGET_OS_TV
//NOT_IB_DESIGNABLE
@interface FMMetadataLabel : UILabel

#else
@interface FMMetadataLabel : MarqueeLabel

#endif

/**
 
 This value is assigned to the `text` property with substitutions
 whenever the currently playing song changes. See the class overview
 for the list of substitutions.
 
 */

@property (strong, nonatomic) IBInspectable NSString *format;

@end
