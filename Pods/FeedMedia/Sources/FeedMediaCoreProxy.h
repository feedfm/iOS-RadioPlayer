//
//  FeedMediaCoreProxy.h
//  FeedMedia
//
//  In the CocoaPod library, the Core stuff is not a separate
//  module, so the #includes are different. This file picks
//  the proper #include
//
//  Created by Eric Lambrecht on 9/11/17.
//  Copyright © 2017 Feed Media. All rights reserved.
//

#ifndef FeedMediaCoreProxy_h
#define FeedMediaCoreProxy_h

#ifdef COCOAPODS
#include "FeedMediaCore.h"
#else
#include <FeedMediaCore/FeedMediaCore.h>
#endif

#endif /* FeedMediaCoreProxy_h */
