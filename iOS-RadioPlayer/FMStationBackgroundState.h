//
//  FMStationBackgroundState.h
//
//  Created by Eric Lambrecht on 6/23/16.
//  Copyright © 2016 Feed Media All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FeedMedia/FeedMediaUI.h>

@interface FMStationBackgroundState : NSObject

@property (strong, nonatomic) NSDate *nextRotationDate;
@property NSTimeInterval secondsRemainingForRotation;
@property (strong, nonatomic) NSMutableArray *images;

@end
