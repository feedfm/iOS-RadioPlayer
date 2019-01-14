//
//  FMShareButton.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 4/30/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMShareButton.h"

@implementation FMShareButton

#if !TARGET_INTERFACE_BUILDER

- (id) initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self setup];
    }
    
    return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self setup];
    }
    
    return self;
}

- (id) init {
    if (self = [super init]) {
        [self setup];
    }
    
    return self;
}

- (void) setup {
    [self addTarget:self action:@selector(onClick) forControlEvents:UIControlEventTouchUpInside];
}

- (void) onClick {
    NSMutableArray *items = [[NSMutableArray alloc] initWithCapacity:3];

    if (_shareText) {
        [items addObject:_shareText];
    }
    
    if (_shareUrl) {
        [items addObject:[NSURL URLWithString:_shareUrl]];
    }
    
    if (_shareImage) {
        [items addObject:_shareImage];
    }
    
    UIActivityViewController *activityViewController =[[UIActivityViewController alloc] initWithActivityItems:items
                                                                                        applicationActivities:nil];
    activityViewController.completionWithItemsHandler = ^(NSString *activityType, BOOL completed, NSArray *returnedItems, NSError *activityError){
        if (activityType) {
            [[FMAudioPlayer sharedPlayer] logEvent:@"share" withParameters:@{@"destination" : activityType }];
        }
    };
    
    UIResponder *uir = (UIResponder *) [self nextResponder];

    // walk up the chain until we find the UIViewController
    // (technically this should be handed to this UIButton, eh?)
    while (uir != nil && ![uir respondsToSelector:@selector(presentViewController:animated:completion:)]) {
        uir = [uir nextResponder];
    }
    
    if (uir != nil) {
        UIViewController *vc = (UIViewController *)uir;
        
        [vc presentViewController:activityViewController
                     animated:YES
                   completion:nil ];
    }
}

#endif

@end
