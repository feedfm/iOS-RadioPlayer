//
//  FMElapsedTimeLabel.h
//  iOS-UI-SDK
//
//  This class extends UILabel to automatically set its
//  text to be the elapsed time of the currently playing
//  song (and it is updated every .5 second), or the
//  value of the textForNoTime property when
//  no song is playing. The setText: call is stubbed out
//  so that the text cannot be changed by the client.
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

//NOT_IB_DESIGNABLE
@interface FMElapsedTimeLabel : UILabel

@property (strong, nonatomic) IBInspectable NSString *textForNoTime;

@end
