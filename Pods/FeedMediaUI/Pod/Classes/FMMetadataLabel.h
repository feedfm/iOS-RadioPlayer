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

#ifdef COCOAPODS
#import <MarqueeLabel/MarqueeLabel.h>
#else
#import "MarqueeLabel.h"
#endif

//NOT_IB_DESIGNABLE
@interface FMMetadataLabel : MarqueeLabel

@property (strong, nonatomic) IBInspectable NSString *format;

@end
