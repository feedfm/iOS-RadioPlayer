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

@property (readonly, nonnull) NSString *name;

/*
 *  Globally unique ID for this station. This value should not be cached by
 *  clients to retrieve favorited stations - they should only use the station
 *  name (this is because as the contents of a station change, so does the
 *  id).
 */

@property (readonly, nonnull) NSString *identifier;

/**
 *  Options dictionary. Contact feed.fm to have data specific to your app
 *  appear here!
 */

@property (readonly, nullable) NSDictionary *options;

/**
 * When true, this station is on-demand, and `-audioFiles` contains
 * an array of songs available for playback in this station.
 */

@property (readonly) BOOL isOnDemand;

/**
 * Used internally to adjust volume of songs from this station.
 */

@property (readonly) double preGain;

/**
 * Used internally to detect if this is a simulcast stream or not
 */

@property (readonly, nonnull) NSString *castURL;

/**
 * Return true if this station is a simulcast station
 */

@property (readonly) BOOL isSimulcast;

/**
 * An array of FMAudioItem songs that are in this station, if it
 * is on-demand, otherwise this is NULL.
 */

@property (nullable) NSArray *audioItems;

/**
 * Representation of the object in dictionary form
 */

//@property (readonly) NSDictionary* jsonDictionary;

/**
 * Returs true if this object is a offline/downloadable station.
 */

@property (readonly) BOOL isTypeOffline;

/**
 * Returns expiry date for offline stations, null for online stations.
 */

@property (readonly, nullable) NSDate *expiry;

/*
 *  JSON representation of this object
 */
@property (readonly, nonnull) NSMutableDictionary *dict;
/*
 *  Used internally to convert the JSON representation of this
 *  station to this object.
 *
 *  @param jsonDictionary JSON dictionary
 *  @return returns new FMStation instance
 */
- (nonnull id)initWithJSON:(nonnull id)jsonDictionary isTypeOffline:(BOOL)isOffline;

@end
