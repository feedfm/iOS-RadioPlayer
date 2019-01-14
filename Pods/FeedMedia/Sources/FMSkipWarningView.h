//
//  FMSkipWarningView.h
//  iOS-UI-SDK
//
//
//  Created by Eric Lambrecht on 4/27/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FeedMediaCoreProxy.h"


/**
 
 This view is meant to temporarily display something to the user when a skip fails.
 This view might have a `UILabel` child that displays 'Sorry, you have temporariy run out
 of skips'.
 
 This view makes itself hidden by default, but sets `hidden` to `true` for
 3 seconds after a skip attempt has failed.
 
 */

//NOT_IB_DESIGNABLE
@interface FMSkipWarningView : UIView

@end
