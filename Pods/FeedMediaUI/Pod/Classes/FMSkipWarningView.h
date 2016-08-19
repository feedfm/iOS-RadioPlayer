//
//  FMSkipWarningView.h
//  iOS-UI-SDK
//
//  This UIView extension just alters its 'hidden' property when the user is
//  to be told that he/she can't skip the current song. This class sets 'hidden'
//  to 'true' when it is created, then it sets it to 'false' when the Feed
//  player sends out an event to notify of failed song skip request, then 3
//  seconds later it sets 'hidden' back to 'true'.
//
//  The idea is that you put your 'sorry, you can't skip' UILabel inside of this
//  view, and it is only displayed when a skip fails, and only for a little bit.
//  Admittedly, this isn't very animated or fun, but it shows a simple way to handle
//  this.
//
//  Created by Eric Lambrecht on 4/27/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import <UIKit/UIKit.h>

//NOT_IB_DESIGNABLE
@interface FMSkipWarningView : UIView

@end
