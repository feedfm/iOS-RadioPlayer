//
//  FMStationArray.h
//  FeedMediaCore
//
//  Created by Eric Lambrecht on 8/16/18.
//  Copyright © 2018 Feed Media. All rights reserved.
//

#ifndef FMSTATIONARRAY_H

#define FMSTATIONARRAY_H

#import <Foundation/Foundation.h>
#import "FMStation.h"

/**
 This is a simple subclass of NSArray that has methods to
 assist with picking out stations based on metadata stored in their
 `options` attribute. See `getStationWithOptions:` for the best
 example.
 */

@interface FMStationArray : NSArray

- (instancetype) initWithStations: (NSArray<FMStation *> *)stations;

/**
 * Search through the stations in this array and return the one that has
 * an option attribute named `key` with a value of `value` (matched with
 * `[value isEqual:entryValue]` or an array of values, one of which matches
 * `value`.
 *
 * @param key name of attribute to inspect
 * @param value attribute value that matching station should contain
 * @return the first station with matching key/value pair or nil
 */

- (FMStation *) getStationWithOptionKey: (NSString *) key Value: (NSObject *) value ;

/**
 * Search through the stations in this array and return the first one
 * that has an option with the given key.
 *
 * @param key name of attribute to search for
 * @return the first station with an option attribute with the given key or nil
 */

- (FMStation *) getStationWithOptionKey: (NSString *) key;

/**
 * Search through the stations in this array and return all
 * that have an option with the given key.
 *
 * @param key name of attribute to search for
 * @return all stations with an option attribute with the given key. never nil.
 */

- (FMStationArray *) getAllStationsWithOptionKey: (NSString *) key;

/**
  Search through the stations in this array and return one that has
  options that match those passed in via optionKeysAndValues. This differs from
  `getStationWithOptionKey:Value:` in that you can specify multiple key/value
  pairs.
 
  This method returns the first station with the matching values, or nil.
 
  A sample query might look like this:
 
     [stations getStationWithOptions: @{ @"genre": @"80s", @"bpm" : @"slow" }
 
  When run against stations with the following options values:
 
     stationA.options = @{ @"genre": @"80s", @"bpm": @"fast" };
     stationB.options = @{ @"genre": @"90s", @"bpm": @"slow" };
     stationC.options = @{ @"genre": @"80s", @"bpm": @"slow", @"something": @"else" };
     stationD.options = @{ @"genre": @"90s" };
 
  this method would return `stationC`.
 
  When an option value is an array, this method will look for an element in the
  array that matches the search value.
 
  The following station would match the query above:
 
     stationE.options = @{ @"genre": @[ @"80s", @"hip-hop", @"rap" ], @"bpm": @"slow" };
 
  @param optionKeysAndValues key value pairs to search for
  @return the first station whose options contain optionKeysAndValues or nil
 */

- (FMStation *) getStationWithOptions: (NSDictionary *) optionKeysAndValues;

/**
  Similar to `getStationWithOptions:`, but this method returns all the stations
  that match the passed in `optionsKeysAndValues` rather than just the first.
 
 see `getStationWithOptions:` for the format of `optionsKeysAndValues`
 
  @param optionKeysAndValues key value pairs to search for (see `getStationWithOptions:`)
  @return an array of stations whose options contain optionKeysAndValues. never nil.
 */

- (FMStationArray *) getAllStationsWithOptions: (NSDictionary *) optionKeysAndValues;

/**
 * Search the stations in this array and return the first one with the
 * given name.
 *
 * @param name name of station to look for
 * @return the first station whose name matches
 */

- (FMStation *) getStationWithName: (NSString *) name;

@end

#endif

