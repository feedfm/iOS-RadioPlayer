//
//  FMAudioPlayer.h
//  sdktest
//
//  Created by James Anthony on 3/7/13.
//  Copyright (c) 2013 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FMStation.h"
#import "FMAudioItem.h"
#import "FMError.h"
#import "FMLog.h"

/**
 *  @const FMAudioPlayerPlaybackStateDidChangeNotification
 *  @discussion Sent when <FMAudioPlayer> state is changed.
 *  <FMAudioPlayer> instance is sent as [NSNotification object]
 *  Observe <playbackState> property for the exact state.
 */
extern NSString *const FMAudioPlayerPlaybackStateDidChangeNotification;

/**
 *  @const FMAudioPlayerCurrentItemDidChangeNotification
 *  @discussion Sent when currently playing item is changed
 */
extern NSString *const FMAudioPlayerCurrentItemDidChangeNotification;

/**
 *  @const FMAudioPlayerActiveStationDidChangeNotification
 *  Sent when active station is changed
 */
extern NSString *const FMAudioPlayerActiveStationDidChangeNotification;

/**
 *  Currently not in use
 */
extern NSString *const FMAudioPlayerAvailableNotification;

/**
 *  Currently not in use
 */
extern NSString *const FMAudioPlayerNotAvailableNotification;

/**
 *  @const FMAudioPlayerSkipStatusNotification
 *  Sent when current item skip status is changed. Its userInfo dictionary contains
 *  'canSkip' key which value means whether you can skip current item.
 *  @see [FMAudioPlayer canSkip]
 */
extern NSString *const FMAudioPlayerSkipStatusNotification;

/**
 *  @const FMAudioPlayerSkipFailedNotification
 *  Sent when current skip request is failed. Its userInfo contains pointer to NSError
 *  object for FMAudioPlayerSkipFailureErrorKey key
 */
extern NSString *const FMAudioPlayerSkipFailedNotification;

/**
 *  @const FMAudioPlayerSkipFailureErrorKey
 *  A userInfo key for FMAudioPlayerSkipFailedNotification
 */
extern NSString *const FMAudioPlayerSkipFailureErrorKey;

/**
 *  @const FMAudioPlayerLikeStatusChangeNotification
 *  Sent by [FMAudioPlayer like] and [FMAudioPlayer dislike] methods.
 *  Its object property points to the current FMAudioPlayer instance.
 */
extern NSString *const FMAudioPlayerLikeStatusChangeNotification;

/// Currently not in use
extern NSString *const FMAudioPlayerStationListAvailableNotification;

/**
 *  @const FMAudioPlayerTimeElapseNotification
 *  Sent every half a second during playback to report changing time.
 *  @see [AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:]
 */
extern NSString *const FMAudioPlayerTimeElapseNotification;

/**
 *  @const FMAudioPlayerStationListKey
 *  userInfo key for NSArray of FMStations from <FMAudioPlayerStationListAvailableNotification>
 */
extern NSString *const FMAudioPlayerStationListKey;

/**
 *  @const FMAudioFormatMP3
 *  Equals to @"mp3"
 */
extern NSString *const FMAudioFormatMP3;
/**
 *  @const FMAudioFormatAAC
 *  Equals to @"aac"
 */
extern NSString *const FMAudioFormatAAC;

/**
 *  @abstract Audio player state.
 *  @see FMAudioPlayerPlaybackStateDidChangeNotification
 */
typedef NS_ENUM(NSInteger, FMAudioPlayerPlaybackState) {
    /**
     *  Audio player item is preparing for playback.
     */
    FMAudioPlayerPlaybackStateWaitingForItem,
    /**
     *  Initial state of the audio player
     */
    FMAudioPlayerPlaybackStateReadyToPlay,
    /**
     *  Player is playing
     */
    FMAudioPlayerPlaybackStatePlaying,
    /**
     *  Playback is paused
     */
    FMAudioPlayerPlaybackStatePaused,
    /**
     *  Some media did not arrive in time to continue playback
     */
    FMAudioPlayerPlaybackStateStalled,
    /**
     *  It is just requested to skip current player item.
     *  @see skip
     */
    FMAudioPlayerPlaybackStateRequestingSkip,
    /**
     *  Some item has been sucessfully skipped or we don't have anything to play
     */
    FMAudioPlayerPlaybackStateComplete
};


#define kFMRemoteControlEvent @"FMRemoteControlEvent"


// for logging:
@protocol FMAudioPlayerLogger<NSObject>
/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event Log message
 */
- (void)logEvent: (NSString *)event;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event      Log message
 *  @param parameters Parameters
 */
- (void)logEvent: (NSString *)event
  withParameters: (NSDictionary *)parameters;
@end

/**
 *  Audio player.
 *  You should get reference to it using [FMAudioPlayer sharedPlayer]
 *  method.
 */
@interface FMAudioPlayer : NSObject

///-----------------------------------------------------
/// @name Initial Setup
///-----------------------------------------------------

+ (void)setClientToken:(NSString *)token secret:(NSString *)secret;
+ (FMAudioPlayer *)sharedPlayer;

///-----------------------------------------------------
/// @name Audio Playback
///-----------------------------------------------------

/**
 *  Prepares current audio item for the playback
 */
- (void)prepareToPlay;

/**
 *  Requests current item to play
 */
- (void)play;

/**
 *  Pauses playback
 */
- (void)pause;

/**
 *  Stops playback
 */
- (void)stop;

/**
 *  Request to skip current player item.
 *  @see FMAudioPlayerPlaybackStateRequestingSkip
 */
- (void)skip;

/**
 *  value between 0.0 and 1.0 relative to system volume
 */
@property (nonatomic) float mixVolume;
/**
 *  Current player statate
 */
@property (nonatomic, readonly) FMAudioPlayerPlaybackState playbackState;
/**
 *  The current time of the currently played item (readonly).
 */
@property (nonatomic, readonly) NSTimeInterval currentPlaybackTime;
/**
 *  Indicates the duration of the current item (readonly).
 */
@property (nonatomic, readonly) NSTimeInterval currentItemDuration;
/**
 *  The current rate of playback. Seeking is not supported, so this will always be 0.0 or 1.0
 */
@property (nonatomic, readonly) float currentPlaybackRate;
/**
 *  Indicates if current item is prepared to play (readonly).
 */
@property (nonatomic, readonly) BOOL isPreparedToPlay;
@property (nonatomic, readonly) FMAudioItem *currentItem;
@property (nonatomic, weak) id<FMAudioPlayerLogger> logger;
@property (nonatomic, readonly) NSArray *stationList;
/**
 *  Indicates if you can skip current item (readonly).
 *  @see skip
 */
@property (readonly) BOOL canSkip;

///-----------------------------------------------------
/// @name Configuring The Session
///-----------------------------------------------------

/**
 *  Active station
 */
@property (nonatomic, copy) FMStation *activeStation;

/**
 *  Finds a station with the given name and sets it as active station
 *
 *  @param name Station name. Should not be nil.
 *
 *  @return true if a station with the given name found
 *  @see activeStation
 */
- (BOOL) setActiveStationByName: (NSString *)name;

/**
 *  Call one of the callbacks as soon as we know if we pass geographic restrictions
 *
 *  @param onAvailable    called when available
 *  @param onNotAvailable called when becomes unavailable
 */
- (void)whenAvailable: (void (^)()) onAvailable
         notAvailable: (void (^)()) onNotAvailable;

/**
 *  Assigns an image to the lock screen when the player is playing
 *
 *  @param image The image to be added to the lock screen
 */
- (void)setLockScreenImage: (UIImage *)image;


/**
 Order specifies priority (earlier elements are preferred).
 Nil-ing this property will allow any format to be served, but is not recommended.
 Set to @[FMAudioFormatMP3] to exclude AAC files.
 Defaults to @[FMAudioFormatAAC,FMAudioFormatMP3].
 */
@property (nonatomic, strong) NSArray *supportedAudioFormats;

/**
 * Set to specify available bandwidth, in kbps. Set to 0 to request the highest available quality.
 * Defaults to 48.
 */
@property (nonatomic) NSInteger maxBitrate;

/**
 *  Set the status like to the current <FMAudioItem> and sends FMAudioPlayerLikeStatusChangeNotification.
 *  @see [FMAudioItem like]
 */
- (void)like;
/**
 *  Set the status dislike to the current <FMAudioItem> and sends FMAudioPlayerLikeStatusChangeNotification.
 *  @see [FMAudioItem dislike]
 */
- (void)dislike;

/**
 *  Set the status unlike to the current <FMAudioItem>. Does *not* send
 *  FMAudioPlayerLikeStatusChangeNotification.
 */
- (void)unlike;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event Log message
 */
- (void) logEvent: (NSString *)event;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event      Log message
 *  @param parameters Parameters
 */
- (void) logEvent: (NSString *)event
   withParameters: (NSDictionary *)parameters;


@end
