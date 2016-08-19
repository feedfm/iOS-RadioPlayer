//
//  FMStationButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 5/14/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

//NOT_IB_DESIGNABLE
@interface FMStationButton : UIButton

@property (nonatomic, strong) IBInspectable NSString *stationName;
@property (nonatomic) IBInspectable BOOL playOnClick;

@end
