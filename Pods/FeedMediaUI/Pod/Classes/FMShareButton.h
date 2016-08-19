//
//  FMShareButton.h
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 4/30/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

//NOT_IB_DESIGNABLE
@interface FMShareButton : UIButton

@property (strong, nonatomic) IBInspectable NSString *shareText;
@property (strong, nonatomic) IBInspectable NSString *shareUrl;
@property (strong, nonatomic) IBInspectable UIImage *shareImage;

@end

