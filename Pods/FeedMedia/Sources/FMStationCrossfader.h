//
//  FMStationCrossfader.h
//  FeedMedia
//
//  Created by Eric Lambrecht on 9/21/17.
//  Copyright © 2017 Feed Media. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The FMStationCrossfader allows you to tie music player actions (such as station changes
 * and volume changes) to cue points. The basic use case is to change stations and volume
 * while playing instructional audio in a separate audio player.
 *
 * Basic class usage works like so:
 * Create an instance of the class with an array of time offsets (cue points) and the actions
 * you want to happen at those times. The current implementation allows you to change the
 * current station or volume. You can create an instance like so:
 *
 *    FMStationCrossfader *cf = [FMSTationCrossfade stationCrossfaderWithInitialStation:@{ @"bpm": @"slow" },
 *                                               andCuePoints: @[
 *                                                      // at 5 seconds in, change the volume to 0.5
 *                                                      5.0f, @0.5f,
 *                                                      // also at 5 seconds in, crosfade to the station
 *                                                      // with a 'bpm' value of 'medium'
 *                                                      5.0f, @{ @"bpm": @"medium" },
 *                                                      // at 10 seconds in, change volume to 1.0
 *                                                      10.0f, @1.0f,
 *                                                      // and crossfade to station with 'bpm' of 'high'
 *                                                      10.0f, @{ @"bpm": @"high" }
 *                                               ]];
 *
 * Alternatively, you can create an instance of the class with no cue points and then use
 * playStation:startingAtTime: and setVolume:startingAtTime to add cue points.
 *
 * When you have added all the cue points, make a call to:
 *
 * [cf connect];
 *
 * Now, as your external media elapses, inform the station crossfader:
 *
 * [cf elapseToTime: _externalMediaPlayer.currentElapsedTime]
 *
 * which call will cause the crossfader to update the current station and volume
 * settings as per the cue points.
 *
 * When any external media that the cue points are connected to starts playback
 * or pauses playback, you should call `[cf play]` or `[cf pause]`.
 *
 * If the user pauses playback of music (independent of your external media), then
 * call [cf disconnect] so that music stays paused until the user turns it back on
 * again. When the user wants to resume playback, call [cf reconnect].
 */

@interface FMStationCrossfader : NSObject

/**
 * Create a new FMStationCrossfader instance. The station passed in is considered the
 * initial station for playback, and cuepoints is an array of alternating time offsets and station
 * specifiers/volume settings that indicate when the station should change or the volume
 * should change.
 *
 * This call:
 *
 *   FMStationCrossfader *cf = [FMSTationCrossfade stationCrossfaderWithInitialStation:@{ @"bpm": @"slow" },
 *                                               andCuePoints: @[
 *                                                      // change station to one with a "bpm" value of "medium"
 *                                                      5.0f, @{ @"bpm": @"medium" },
 *                                                      // change station to one with a "bpm" value of "high"
 *                                                      10.0f, @{ @"bpm": @"high" },
 *                                                      // change volume to 0.2
 *                                                      0.0f, @0.2f
 *                                                      // change volume to 1.0
 *                                                      8.0f, @1.0f
 *                                               ]];
 *
 * Would make the station with 'slow' bpm active from 0 seconds in to 5 seconds in, then
 * the station with 'medium' bpm active from 5 seconds to 10 seconds, then the station with
 * 'high' bpm active from 10 seconds to the end of the song. The music player volume will be set
 * to 0.2 starting a 0 seconds in, and then changed to 1.0 at 8 seconds in.
 *
 * Setting the intial station to nil means the player starts out paused until a station change
 * cuepoint is hit.
 *
 * CuePoints do not need to be in order, as they are ordered when the 'connect' call is
 * made later.
 *
 * @param initialStationOptionKeysAndValues a set of key/value pairs that will be passed to
 *      FMAudioPlayer getStationWithOptionKey:Value: to get the intial station for playback
 * @param cuePoints an array that holds alternating NSFloats that specify time indexes and
 *       either station queries or volume values
 * @return a new FMStationCrossfader object
 */

+ (FMStationCrossfader *) stationCrossfaderWithInitialStation: (NSDictionary *) initialStationOptionKeysAndValues
                                                  andCuePoints: (NSArray *) cuePoints;

/**
 * Create a new FMStationCrossfader instance with a default station. Cue points can be
 * added with the playStation:startingAtTime and setvolume:startingAtTime: methods.
 *
 * @param initialStationOptionKeysAndValues a set of key/value pairs that will be passed to
 *      FMAudioPlayer getStationWithOptionKey:Value: to get the intial station for playback
 * @return a new FMStationCrossfader object
 */

+ (FMStationCrossfader *) stationCrossfaderWithInitialStation: (NSDictionary *) initialStationOptionKeysAndValues;

/**
 * Specify that the station specified by optionKeysAndValues should be active starting
 * at the given time.
 *
 * Calls to this method must be made before calling 'connect'
 *
 * @param optionKeysAndValues a set of key/value pairs that will be passed to
 *      FMAudioPlayer getStationWithOptionKey:Value: to find a station
 * @param time the time at which the named station should become active.
 */

- (void) playStation: (NSDictionary *) optionKeysAndValues startingAtTime: (float) time;

/**
 * Specify that the music player volume should be set to the given volume starting at
 * the given time.
 *
 * Calls to this method must be made before calling 'connect'
 *
 * @param volume an NSNumber whose float value is from 0.0 to 1.0
 * @param time the time at which the named station should become active.
 */


- (void) setVolume: (NSNumber *) volume startingAtTime: (float) time;

/**
 * This resets the player, changes the active station to the initial station
 * and starts queueing up the first song.
 */

- (void) connect;

/**
 * Call this to start or resume music playback rather than directly calling
 * the global shared player instance.
 */

- (void) play;

/**
 * Call this to pause music playback rather than directly calling the global
 * shared player instance.
 */

- (void) pause;

/**
 * If the user hits pause while music is playing, then disconnect should be called to
 * prevent this class from updating playback (even if elapseTotime: is called) until
 * the user resumes music playback.
 */

- (void) disconnect;

/**
 * If the user hits play after disconnecting, then reconnect should be called so 
 * stations are updated by this class again.
 */

- (void) reconnect;

/**
 * This call causes the active station in the shared FMAudioPlayer to be updated to match
 * the station that should be active at `time`. This method should be called at regular intervals
 * while the external media is playing.
 *
 * @param time current number of seconds elapsed in external media.
 */

- (void) elapseToTime: (float) time;

@end

