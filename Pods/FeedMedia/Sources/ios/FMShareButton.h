//
//  FMShareButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 4/30/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"

/**
 
 This button will respond to a tap by bringing up an iOS sharing
 interface and passing to it some text, url, and image.
 
 */

//NOT_IB_DESIGNABLE
@interface FMShareButton : UIButton

/**
 Text to be shared, if any.
 */

@property (strong, nonatomic) IBInspectable NSString *shareText;

/**
 URL to be shared, if any.
 */
@property (strong, nonatomic) IBInspectable NSString *shareUrl;

/**
 Image to be shared, if any.
 */

@property (strong, nonatomic) IBInspectable UIImage *shareImage;

@end

