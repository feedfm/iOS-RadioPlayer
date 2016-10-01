//
//  FMStation.h
//  sdktest
//
//  Created by James Anthony on 3/11/13.
//  Copyright (c) 2013-2016 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This object represents a Feed.fm radio station, from which songs are
 * retrieved. 
 *
 * After an `FMAudioPlayer` is initialized, a list of available stations
 * can be found in the `-FMAudioPlayer:stationList` array.
 *
 * The `-options` dictionary contains arbitrary metadata about this station
 * that is passed on from the server, such as: background imagery, descriptive
 * text, keywords, e.t.c. Talk to feed.fm to have these values set to
 * whatever you wish.
 **/

@interface FMStation : NSObject <NSCopying>

/**
 *  Station name
 */

@property (readonly) NSString *name;

/*
 *  Globally unique ID for this station. This value should not be cached by
 *  clients to retrieve favorited stations - they should only use the station
 *  name (this is because as the contents of a station change, so does the
 *  id).
 */

@property (readonly) NSString *identifier;

/**
 *  Options dictionary. Contact feed.fm to have data specific to your app
 *  appear here!
 */

@property (readonly) NSDictionary *options;

/*
 *  Used internally to convert the JSON representation of this
 *  station to this object.
 *
 *  @param jsonDictionary JSON dictionary
 *  @return returns new FMStation instance
 */
- (id)initWithJSON:(id)jsonDictionary;

@end
