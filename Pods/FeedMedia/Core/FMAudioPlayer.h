//
//  FMAudioPlayer.h
//  sdktest
//
//  Created by James Anthony on 3/7/13.
//  Copyright (c) 2013-2016 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FMStation.h"
#import "FMAudioItem.h"
#import "FMError.h"
#import "FMLog.h"
#import "FMAudioPlayer.h"
#import "FMLockScreenDelegate.h"
#import "FMStationArray.h"

#if TARGET_OS_TV
#else
#import "CWStatusBarNotification.h"
#endif


NS_ASSUME_NONNULL_BEGIN

/**
 *  @const FMAudioPlayerPlaybackStateDidChangeNotification
 *  @discussion Sent when <FMAudioPlayer> state is changed.
 *  <FMAudioPlayer> instance is sent as [NSNotification object]
 *  Observe <playbackState> property for the exact state. This will
 *  be the first event issued by the library, and the state will
 *  either be <FMAudioPlayerPlaybackStateUnavailable> or <FMAudioPlayerPlaybackStateReadyToPlay>.
 */
extern NSString *const FMAudioPlayerPlaybackStateDidChangeNotification;

/**
 *  @const FMAudioPlayerCurrentItemDidBeginPlaybackNotification
 *  @discussion Sent when a new song has begun playback. Code that responds
 *    to this event can expect [FMAudioPlayer currentItem] to be non-nil.
 *    This event is only triggered once for any song (and not, for instance,
 *    after resuming playbck from a pause)
 */

extern NSString *const FMAudioPlayerCurrentItemDidBeginPlaybackNotification;

/**
 *  @const FMAudioPlayerMusicQueuedNotification
 * @discussion Sent when the player has loaded music from the current
 * station and is ready for immediate playback. This is triggered by a
 * call to `prepareToPlay`.
 */
 
extern NSString *const FMAudioPlayerMusicQueuedNotification;

/**
 *  @const FMAudioPlayerActiveStationDidChangeNotification
 *  Sent when active station is changed via one of the [FMAudioPlayer setActiveStation]
 *  calls.
 */
extern NSString *const FMAudioPlayerActiveStationDidChangeNotification;

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

/**
 *  @const FMAudioPlayerTimeElapseNotification
 *  Sent every half a second during playback to report changing time.
 *  @see [AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:]
 */
extern NSString *const FMAudioPlayerTimeElapseNotification;

/**
 *  @const FMAudioPlayerPreCachingCompleted
 *  Sent when precaching for stations is completed. This notification
 * is sent after a call to `prepareStations` or `prepareStations:`
 * completes.
 *  
 */
extern NSString *const FMAudioPlayerPreCachingCompleted;

/**
 * @const FMAudioPlayerNewClientIdAvailable
 *
 * Sent to notify sucessful generation of a new client Id.
 */

extern NSString *const FMAudioPlayerNewClientIdAvailable;

/**
 *  @const FMAudioPlayerStationDownloadProgress
 *  Sent to indicate progress for station download
 *
 */
extern NSString *const FMAudioPlayerStationDownloadProgress;
/**
 *  @const FMAudioPlayerStationListKey
 *  userInfo key for NSArray of FMStations from <FMAudioPlayerStationListAvailableNotification>
 */
extern NSString *const FMAudioPlayerStationListKey;

/**
 * @const FMAudioItemKey
 * userInfo key for FMAudioItem object sent with <FMAudioPlayerLikeStatusChangeNotification>
 */

extern NSString *const FMAudioItemKey;

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
 * @enum This enum represents the various states the FMAudioPlayer can
 * be in, as identified by the `[FMAudioPlayer playbackState]`.
 */
typedef NS_ENUM(NSInteger, FMAudioPlayerPlaybackState) {
    
    /**
     * Offline music is available
     *
     */
    
    FMAudioPlayerPlaybackStateOfflineOnly,
    
    /**
     * The server has not responded yet, so we don't know if music
     * is available or not yet.
     */
     
    FMAudioPlayerPlaybackStateUninitialized,
    
    /**
     * The server has told us that we cannot stream music.
     */
    
    FMAudioPlayerPlaybackStateUnavailable,
    
    /**
     *  The player is waiting for the server to give it the next song for playback.
     */
    FMAudioPlayerPlaybackStateWaitingForItem,
    
    /**
     *  Initial state of the audio player.
     */
    FMAudioPlayerPlaybackStateReadyToPlay,
    
    /**
     *  Playback of audio is in progress
     */
    FMAudioPlayerPlaybackStatePlaying,
    
    /**
     *  Playback is paused
     */
    FMAudioPlayerPlaybackStatePaused,
    
    /**
     *  Some media did not arrive in time to continue playback, and the 
     *  player is waiting for more audio data to arrive.
     */
    FMAudioPlayerPlaybackStateStalled,
    
    /**
     * The user has requested that the current song be skipped, and the
     * player is waiting for word back from the server if the skip
     * will be allowed.
     */
    FMAudioPlayerPlaybackStateRequestingSkip,
    
    /**
     * When there is no more music to play in the current station, the
     * player enters this state.
     */
    FMAudioPlayerPlaybackStateComplete
};

NS_ASSUME_NONNULL_END
#define kFMRemoteControlEvent @"FMRemoteControlEvent"

/**
 When a station download request is posted this delegate
 is required to track the progress and the completion of the download.
 */

@protocol FMStationDownloadDelegate <NSObject>

/**
 This method is called once, at the start of a station download,
 and then again after every file in the station is either fully
 downloaded or aborted.
 
 The first (and possibly final) call to this method will have 0
 failed counts and pending and total will be the number of
 files that will be downloaded for the station.
 
 The final call to this method will have a pendingCount value of 0 
 
 @param station The station that is being downloaded
 @param pendingCount the number of downloads remaining to be downloaded. The last
   call to this method will have pendingCount == 0
 @param failedCount the number of download attempts that failed
 @param totalCount the total number of files that will be downloaded
 */
-(void) stationDownloadProgress:(nonnull FMStation*)station
                    pendingCount:(int)pendingCount
                     failedCount:(int)failedCount
                      totalCount:(int)totalCount;

@end


/**
 When events are reported to the feed.fm servers via
 `[FMAudioPlayer logEvent]` and `[FMAudioPlayer logEvent:withParameters]`,
 those events will also be reported to any class implementing
 this protocol and assigned to the `[FMAudioPlayer logger]` property.
 
 The SDK uses the `[FMAudioPlayer logEvent]` internally, so this
 is an interface for apps to receive copies of events that feed.fm
 tracks internally so they may be passed on to other logging frameworks.
 
*/

@protocol FMAudioPlayerLogger<NSObject>
/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event Log message
 */
- (void)logEvent: (nonnull NSString *)event;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the 'logger' property
 *
 *  @param event      Log message
 *  @param parameters Parameters
 */
- (void)logEvent: (nonnull NSString *)event
  withParameters: (nonnull NSDictionary *)parameters;
@end


/**
 
 The SDK centers around a singleton instance of this `FMAudioPlayer` class, which 
 has simple methods to control music playback (`play`, `pause`, `skip`). The
 `FMAudioPlayer` holds lists of `FMStation` objects (`stationList` and `localOfflineStationList`), one of which is always
 considered the _active_ station (`activeStation`). Once music playback has begun, there
 is a _current_ song (`currentSong`).
 
 Typical initialization and setup is as follows:

 As early as you can in your app's lifecycle (preferably in your `AppDelegate`
 or initial `ViewController`) call

     [FMAudioPlayer setclientToken:@"demo" secret:@"demo"]

 to asynchronously contact the feed.fm servers, validate that the client is in a location
 that can legally stream music, and kick of a thread to retrieve a list of available
 streaming music stations.
 
 There are a number of sample credentials you can use to assist
 in testing your app out. Use one of the following strings for your
 token and secret to get the desired behavior:
 
 - 'demo' - 3 simple stations with no skip limits
 - 'badgeo' - feed.fm will treat this client as if it were accessing from outside the US
 - 'counting' - a station that just plays really short audio clips
   of a voice saying the numbers 0 through 9

 To receive notice that music is available or not available, use the
 `whenAvailable:notAvailable:` method call, which is guaranteed to call
 only one of its arguments as soon as music is deemed available or not:

    FMAudioPlayer *player = [FMAudioPlayer sharedPlayer];
 
    [player whenAvailable:^{
      NSLog(@"music is available!");
      // .. do something, now that you know music is available

     } notAvailable: ^{
        NSLog(@"music is not available!");
        // .. do something, like leave music button hidden

     }];

 Because music may not be available to this particular client (due
 to lack of network connectivity or geographic restrictions), we
 recommend you leave music functionality hidden by default, and
 reveal it only when confirmation is returned.

 Once music is available, use the `play`, `pause`, `skip` methods to
 control playback. The `stationList` and `localOfflineStationList` properties
 will contain lists of stations the user can switch to with the `setActiveStation:` and
 `setActiveStation:withCrossfade:` calls.

     // pick the station to play music from
     FMStation *station = [player.stationList getStationWithOptionKey: @"genre" Value: @"HipHop"];
     [player setActiveStation:station withCrossfade:NO];

     // when you have set the station that is about to begin playback, you
     // can optionally call prepareToPlay first so playback is immediate upon
     // calling 'play'
     [player prepareToPlay];
 
     // begin playback!
     // (if you called 'prepareToPlay', then you should first wait for
     // an FMAudioPlayerMusicQueuedNotification notification to be guaranteed
     // that playback will start immediately on this call, with no intervening
     // network requests)
     [player play]
 
 Offline music can be retrieved by selecting a station in the
 `remoteOfflineStationList` and passing it to `downloadAndSyncStation:forTargetMinutes:withDelegate`.
 That will cause the contents of the station to be downloaded onto the device
 (or updated with new music, if the station was already downloaded and new
 music is available), and a new `FMStation` entry in `localOfflineStationList`
 that can be passed to `setActiveStation`.
 
 The `FMAudioPlayer` registers with iOS so that
 playback can be paused, skipped, liked, and disliked via the lock screen.
 Additionally, iOS will display on the lock screen whatever image
 you've assigned via `[FMAudioPlayer setLockScreenImage:]`.
 
 The 'prepareToPlay' method can be called before playback begins and
 when the client knows that the current station will immediately be
 played next. This call is primarily useful when you want music to begin
 playback immediately upon a call to play, with no intervening network
 requests.
 
 The `FMAudioPlayer` generates events that can be hooked into
 whatever analytics service your app uses. Just have an object in your app
 (your `AppDelegate` is a good choice) implement the `FMAudioPlayerLogger`
 protocol. You just need to implement two
 methods: `logEvent:` and `logEvent:withParameters:`,
 and assign the object to `[FeedMedia sharedPlayer].logger`.
 
 For assistance with building music player UI, check out the
 [UI library](http://demo.feed.fm/sdk/docs/ios/ui/latest/html)
 documentation and check out our demo app:
 
 [https://github.com/feedfm/iOS-RadioPlayer](https://github.com/feedfm/iOS-RadioPlayer)
*/

@interface FMAudioPlayer : NSObject

///-----------------------------------------------------
/// @name Setup
///-----------------------------------------------------

/**
 * This method kicks off asynchronous initialization of the library and communication
 * with the feed.fm servers. This call should be made as early as possible
 * in the lifecycle of the app.
 *
 * @param token public authentication token. Use `@"demo"` during testing/development.
 * @param secret private authentication token. Use `@"demo"` during testing/development.
 */

+ (void)setClientToken:(nonnull NSString *)token secret:(nonnull NSString *)secret;

/**
 * There is only one global `FMAudioPlayer` instance, and it
 * is available via this static property.
 */

+ (nonnull FMAudioPlayer *)sharedPlayer;

/**
 * Call one of the two callbacks as soon as we know music is available for
 * playback. One of these two blocks is
 * guaranteed to be called, and only one call will ever be made.
 * Just before the onAvailable callback is made, the list of available stations
 * is fully populated.
 *
 * Note that the callbacks are only made after attempting to contact the Feed.fm
 * servers, even if local offline music is available while waiting for a
 * response. If the player is unable to contact the Feed.fm servers or they
 * respond that no streaming music is available, but there is local offline music,
 * then the onAvailable callback will be called.
 *
 * If the player has already contacted (or failed to contact) the feed.fm
 * servers, then one of the two calls passed callbacks will be called immediately,
 * before this method returns.
 *
 *  @param onAvailable    called when music becomes or already is available
 *  @param onNotAvailable called when we determine music is not available
 */

- (void)whenAvailable: (nonnull void (^)(void)) onAvailable
         notAvailable: (nonnull void (^)(void)) onNotAvailable;


///-----------------------------------------------------
/// @name Playback Controls
///-----------------------------------------------------


/**
 * Starts asynchronous loading of the first song in the active station
 * so that a future call to `play` will start music instantaneously.
 * This action runs asynchronously and, when it completes, triggers
 * an `FMAudioPlayerPreCachingCompleted` notification.
 */
- (void)prepareToPlay;

/**
 * Starts retrieval and playback of music in the active station.
 */
- (void)play;

/**
 * Start playback of specific song. This method only works with
 * on-demand stations.
 *
 * @param audioItem the audio item to immediately play
 */
- (void)playAudioItem: (nonnull FMAudioItem *) audioItem;

/**
 * Pauses music playback.
 */
- (void)pause;

/**
 *  Stops music playback and discards any cached audio.
 */
- (void)stop;

/**
 * Asynchronously request that the player skip the current song. If the
 * request is successful, the current song will stop and the next will
 * begin. If not, an `FMAudioPlayerSkipFailedNotification` will be posted
 * to the default notification center and the current song will continue
 * playback.
 */
- (void)skip;

/**
 * Calls `likeAudioItem:` with the currently playing song
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)like;

/**
 * Marks the specified song as 'liked'. Updates the `[FMAudioItem liked]`
 * and `[FMAudioItem disliked]` properties.
 *
 * This triggers an `FMAudioPlayerLikeStatusChangeNotification` notification
 * with a userInfo dictionary that contains the audioItem
 * object indexed by `FMAudioItemKey`.
 *
 * @param audioItem the audio item that is to be liked. If null, then the currently
 *     active audio item will be liked.
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)likeAudioItem: (nonnull FMAudioItem *)audioItem;

/**
 * Calls `dislikeAudioItem:` with the currently playing song
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)dislike;

/**
 * Marks the specified song as 'disliked'. Updates the `[FMAudioItem liked]`
 * and `[FMAudioItem disliked]` properties. 
 *
 * This triggers an `FMAudioPlayerLikeStatusChangeNotification` notification
 * with a userInfo dictionary that contains the audioItem
 * object indexed by `FMAudioItemKey`.
 *
 * @param audioItem the audio item that is to be disliked. If null, then the currently
 *     active audio item will be disliked.
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)dislikeAudioItem: (nonnull FMAudioItem *)audioItem;

/**
 * Calls `unlikeAudioItem:` with the currently playing song
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)unlike;

/**
 * Marks the specified song as neither 'liked' nor 'disliked'. Updates the `[FMAudioItem liked]`
 * and `[FMAudioItem disliked]` properties.
 *
 * This triggers an `FMAudioPlayerLikeStatusChangeNotification` notification
 * with a userInfo dictionary that contains the audioItem
 * object indexed by `FMAudioItemKey`.
 *
 * @param audioItem the audio item that is to be unliked. If null, then the currently
 *     active audio item will be unliked.
 *
 * @see [FMAudioItem liked]
 * @see [FMAudioItem disliked]
 */
- (void)unlikeAudioItem: (nonnull FMAudioItem *)audioItem;

/**
 * Sets a previously generated clientid to be the active id.
 *
 * @param cid previously generated client id
 */

- (void) setClientId: (nonnull NSString*) cid;

/**
 * Asynchronous generate a new client id for a new user.
 * When this request is complete a NSNotification `FMAudioPlayerNewClientIdAvailable` is triggered
 * with userInfo dictionary that contains the clientid
 *
 * @see setClientId:
 */
- (void) createNewClientId;


///-----------------------------------------------------
/// @name Playback Status
///-----------------------------------------------------

/**
 * Current player state. As this state changes, an `FMAudioPlayerPlaybackStateDidChangeNotification`
 * is triggered with the default notification center.
 */

@property (nonatomic, readonly) FMAudioPlayerPlaybackState playbackState;

/**
 * The currently playing or paused song, or null if there
 * is not one.
 */
@property (nonatomic, readonly, nullable)  FMAudioItem *currentItem;


/**
 *  The elapsed playback time of the current item.
 */

@property (nonatomic, readonly) NSTimeInterval currentPlaybackTime;

/**
 *  Indicates the duration of the current item.
 */

@property (nonatomic, readonly) NSTimeInterval currentItemDuration;

/**
 *  The current rate of playback. Slow/fast play is not supported, so this will always be 0.0 or 1.0
 */

@property (nonatomic, readonly) float currentPlaybackRate;

/**
 * If false, then the user may not skip the currently playing
 * song. If true, the user may be able to skip the current song,
 * but the server will be queried and possibly reject the request.
 * This property is updated every time a new song
 * starts playback or after a failed skip attempt, and a
 * `FMAudioPlayerSkipStatusNotification notification` is sent any
 * time this value changes.
 *
 *  @see skip
 */

@property (readonly) BOOL canSkip;

/**
 * This array holds all the FMAudioItems that the user has heard
 * since playback started, including the currently playing
 * song. As new items start playback, they are appended to this array.
 *
 * This history currently does not include songs from past sessions.
 */

@property (nonatomic, readonly, nonnull) NSMutableArray<FMAudioItem *> *playHistory;



///-----------------------------------------------------
/// @name Playback options
///-----------------------------------------------------

/**
 * The number of seconds to crossfade between songs. This defaults
 * to 0.
 */

@property (nonatomic) float secondsOfCrossfade;

/**
 * When crossfading between songs, the song we are transitioning to can either
 * begin playback at full volume or ramp up from silence to full volume during
 * the transition. When this value is true (the default), the song will
 * ramp up.
 */

@property (nonatomic) BOOL crossfadeInEnabled;

/**
 * When true (the default), adjust individual song volumes so they are perceived
 * be the same loudness.
 */

@property (nonatomic) BOOL normalizeSongVolume;


/**
 *  A value between 0.0 and 1.0 relative to system volume
 */

@property (nonatomic) float mixVolume;



///-----------------------------------------------------
/// @name Current and available stations
///-----------------------------------------------------

/**
 * This is a list of streaming music stations retrieved from the server.
 * This array will not change once populated.
 **/

@property (nonatomic, readonly, nonnull) FMStationArray *stationList;


/**
 The list of stations available for immediate offline playback.
 This list contains any stations that have been downloaded at some point
 in the past with downloadAndSyncStation:forTargetMinutes:withDelegate.
 
 Stations listed here are available for playback even if there is no
 network connectivity, and this property is intialized as soon as the
 `FMAudioPlayer` is created (before any attempt is made to contact
 the feed.fm servers.
 
 When there is internet connectivity, every station in this list will
 have a paired station (with the same name, but not necessarily same ID)
 in the remoteOfflineStationList. Use `remoteOfflineStationForLocalOfflineStation:`
 to map to the remote FMStation. If they have different 'identifier' values,
 then the local station should be updated by passing its pair to
 `downloadAndSyncStation:withDelegate`.
 
 @return List of stations available on disk ready for playback. never returns nil.
 */

@property (readonly, nonatomic, nonnull) FMStationArray *localOfflineStationList;


/**
 List of stations that are available for downloading.
 
 These stations cannot be tuned to (with setActiveStation:), rather they should be passed
 to downloadAndSyncSation:forTargetMinutes:withDelegate to be downloaded
 and made available for playback in the localOfflineStationList.
 
 This property is only populated when internet connectivity is available and
 the player is declared 'available'.

 If one of these stations has been downloaded, the `localOfflineStationForRemoteOfflineStation:`
 method can be used to find the local equivalent for playback.
 
 @return List of stations that can be downloaded for offline playback
 */

@property (readonly, nonatomic) FMStationArray  * _Nullable remoteOfflineStationList;


/**
 * The current station from which music is pulled. Any `FMStation` retrieved
 * from the `stationList` or `localOfflineStationList` properties can be assigned here.
 * Once music is available, this property is never null. When this value changes,
 * `FMAudioPlayerActiveStationDidChangeNotification` is sent to the default
 * notification center.
 */

@property (nonatomic, copy, nonnull) FMStation *activeStation;


/**
 * Make the given station the `activeStation`. If
 * `withCrossfade` is true, any currently playing music will crossfade into the first
 * song in the new station.
 *
 *  @param station Station to tune to.
 *  @param withCrossfade if true, if crossfading is enabled, and if music is currenty
 *    playing, the currently playing song will fade into the song in the new station
 *    as soon as it is loaded.
 *
 *  @see activeStation
 */

- (void) setActiveStation: (nonnull FMStation *)station withCrossfade: (BOOL) withCrossfade;



///-----------------------------------------------------
/// @name Offline station management
///-----------------------------------------------------

/**
 Downloads an offline station.
 
 This method kicks off an asynchronous download to retrieve audio
 files for the given station. As the station downloads, events (1
 at a minimum) will be sent to the provided delegate.
 
 The station passed in must come from the `remoteOfflineStationList`
 
 The `minutes` attribute specifies the minimum number of minutes of
 music the client would like to be available offline. The server will make the
 decision as to whether the client already has enough music stored locally
 and, if so, whether that music should be replaced or appended to.
 
 Note that if the requested station has already been downloaded or partially
 downloaded to local storage already, only missing music will be downloaded.
 Some stations can additionally be configured (on the server) so that
 only a subset of the full station contents are saved on client devices,
 and each request to `downloadAndSyncStation:` will cause recently played
 music to be deleted and new music to be downloaded.

 @param remoteStation A station from remoteOfflineStationList
 @param minutes describes target time for music. If you need music for half an hour pass 30.
 @param delegate for receiving updates about the download.
 @see FMStationDownloadDelegate
 
 */

-(void) downloadAndSyncStation:(nonnull FMStation *)remoteStation
              forTargetMinutes:(nullable NSNumber*) minutes
                  withDelegate: (nonnull id<FMStationDownloadDelegate>) delegate;


/**
 Downloads an offline station.
 
 This method is the same as `downloadAndSyncStation:forTargetMinutes:withDelegate`, but
 it lets the server determine the 'targetMinutes' value. This method is preferable
 unless the amount of music to be loaded for each station varies in different contexts
 known only by the client.
 
 @param remoteStation Pass a station from remoteOfflineStationList
 @param delegate for receiving updates about the download.
 @see FMStationDownloadDelegate
 */

-(void) downloadAndSyncStation:(nonnull FMStation *)remoteStation
                  withDelegate: (nonnull id<FMStationDownloadDelegate>) delegate;

/**
 Deletes all locally stored files in a previously downloaded station and
 removes the station from the `localOfflineStationList`.
 
 Does nothing if the station passed in does not
 appear in the `localOfflineStationList` or if the station being
 deleted is the activeStation.
 
 @param localOfflineStation the station whose contents will be deleted.
 */

- (void) deleteOfflineStation: (nonnull FMStation *) localOfflineStation;

/**
 Deletes all locally stored stations.
 
 This call does nothing if the current active station is a local
 offline station.
 */

- (void) deleteAllOfflineStations;

/**
 Map a remote offline station to a local offline station.
 
 This method is useful in determining which of the available remote offline
 stations have been downloaded and stored as local offline stations.
 
 When a remote station is downloaded, a duplicate FMStation instance is added to the
 local offline station array. If the remote station is updated (that is,
 music is added or deleted), then the remote FMStation instance will have an
 ID that differs from the FMStation instance in the local offline station array.
 This station maps the remote FMStation instance to its local FMStation instance,
 regardless of whether their contents match up exactly.
 
 @param remoteOfflineStation a station from remoteOfflineStationList
 @return nil or a station from remoteOfflineStationList
 */

- (nullable FMStation *) localOfflineStationForRemoteOfflineStation: (nonnull FMStation *) remoteOfflineStation;

/**
 Map a locally stored offline station to its remote offline pair.
 
 This method is useful to determine if a locally downloaded station can
 be updated with new music. If the local FMStation `identifier` value
 doesn't match the remote FMStation `identifier` value, then the remote
 FMStation can be passed to `downloadAndSyncStation:withDelegate` to update
 the local FMStation.
 
 @param localOfflineStation a station from localOfflineStationList
 @return a station from remoteOfflineStationList
 */

- (nullable FMStation *) remoteOfflineStationForLocalOfflineStation: (nonnull FMStation *) localOfflineStation;

///-----------------------------------------------------
/// @name Logging and reporting
///-----------------------------------------------------


/**
 * Any calls to `logEvent:` or `logEvent:withParameters:`
 * are also sent to the logger assigned to this property, if
 * any.
 */

@property (nonatomic, weak, nullable) id<FMAudioPlayerLogger> logger;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the `logger` property
 *
 *  @param event Log message
 */
- (void) logEvent: (nonnull NSString *)event;

/**
 *  Everything logged here goes back to Feed.fm and is also cc'd to the `logger` property
 *
 *  @param event      Log message
 *  @param parameters Parameters
 */
- (void) logEvent: (nonnull NSString *)event
   withParameters: (nonnull NSDictionary *)parameters;



///-----------------------------------------------------
/// @name Misc..
///-----------------------------------------------------

/**
 * Order specifies priority (earlier elements are preferred).
 * Nil-ing this property will allow any format to be served, but is not recommended.
 * Set to `FMAudioFormatMP3` to exclude AAC files.
 * Defaults to `@[FMAudioFormatAAC,FMAudioFormatMP3]`.
 *
 * In the normal course of events, clients do not need to make use of this.
 */
@property (nonatomic, strong, nullable) NSArray *supportedAudioFormats;

/**
 * Set to specify available bandwidth, in kbps. Set to 0 to request the highest available quality.
 * Defaults to 48.
 */
@property (nonatomic) NSInteger maxBitrate;

#if TARGET_OS_TV
#else

/**
 * This status bar notification is used to announce song changes to
 * the user. Access the properties on this object to change
 * how the notification is styled and to add handlers for when the
 * notification is tapped.
 *
 * Details on this object can be found at https://github.com/cezarywojcik/CWStatusBarNotification
 */

@property (nonatomic, readonly, nullable) CWStatusBarNotification *statusBarNotification;

#endif

/**
 * The player displays a notification at the top of the screen during song
 * transitions by default. If you are currently showing the active song, which
 * means a notification isn't needed, it can be disabled by setting this
 * property to YES. Don't forget to set this to NO when you stop showing the
 * active song.
 *
 * To alter how notifications are displayed, see the `statusBarNotification`
 * property.
 */

@property (nonatomic) BOOL disableSongStartNotifications;

/**
 * If YES (the default), then the Feed.fm library will
 * register with the MPRemoteCommandCenter to handle play/pause/skip/like/dislike
 * commands upon start of playback. Note that, unless a lockScreenDelegate
 * is assigned, the FMAudioPlayer will still enable/disable the
 * play/pause/skip/like/dislike buttons in the MPRemoteCommandCenter (but not
 * respond to them) when this is NO.
 */

@property (nonatomic) BOOL doesHandleRemoteCommands;

/**
 * When not NULL, this causes the FMAudioPlayer to not update
 * the MPNowPlayingInfoCenter metadata nor enable or disable the like,
 * dislike, and next track MPFeedbackCommands. See the documentation
 * of FMLockScreenDelegate for more information. Note that the
 * FMAudioPlayer will still register to handle the MPRemoteCommandCenter
 * commands (play/pause/skip/like/dislike) unless doesHandleRemoteCommands
 * is also set to NO.
 */

@property (nonatomic, nullable) id<FMLockScreenDelegate> lockScreenDelegate;

/**
 *  Assigns the image to be displayed on the lock screen when music is playing.
 *
 *  @param image The image to be added to the lock screen
 */

- (void)setLockScreenImage: (nonnull UIImage *)image;

/**
 * Utility function to map state to string.
 *
 * @param type the playback state to map to an NSString
 */

+ (nonnull NSString *) nameForType:(FMAudioPlayerPlaybackState)type;


///-----------------------------------------------------
/// @name Deprecated
///-----------------------------------------------------


/**
 @deprecated Clients should use the `FMStationArray` interface to
 search for stations based on option values.
 
 Search throught the list of available stations, and return one that has
 options that match those passed in via optionKeysAndValues. This differs from
 getStationWithOptionKey:Value: in that you can specify multiple key/value
 pairs, like so:
 
   [player getStationWithOptions: @{ @"genre": @"80s", @"bpm" : @"slow" }
 
 This method returns the first station with the matching values, or nil.
 
 @param optionKeysAndValues key value pairs to search for
 @return a station whose options contain optionKeysAndValues
 
 */

- (nullable FMStation *) getStationWithOptions: (nonnull NSDictionary *) optionKeysAndValues DEPRECATED_ATTRIBUTE;

/**
 @deprecated Clients should use the `FMStationArray` interface to
 search for stations based on option values.
 
 Similar to getStationWithOptions:, but this method returns all the stations
 that match the passed in optionsKeysAndValues.
 
 @param optionKeysAndValues key value pairs to search for
 @return an array of stations whose options contain optionKeysAndValues. never nil.
 
 */

- (nullable NSArray<FMStation *> *) getAllStationsWithOptions: (nonnull NSDictionary *) optionKeysAndValues DEPRECATED_ATTRIBUTE;


/**
 * @deprecated Clients should find FMStation references by pulling them from
 * stationList or localOfflineStationList and then assigning the reference
 * to the activeStation property or calling setActiveStation:withCrossfade:
 *
 *  Finds a station with the given name and assigns it to the `activeStation`.
 *
 *  @param name Station name. Should not be nil.
 *
 *  @return true if a station with the given name is found
 *  @see activeStation
 */

- (BOOL) setActiveStationByName: (nonnull NSString *)name DEPRECATED_ATTRIBUTE;

/**
 * @deprecated Clients should find FMStation references by pulling them from
 * stationList or localOfflineStationList and then assigning the reference
 * to the activeStation property or calling setActiveStation:withCrossfade:
 *
 * Finds a station with the given name and assigns it to the `activeStation`. If
 * `withCrossfade` is true, any currently playing music will crossfade into the first
 * song in the new station.
 *
 *  @param name Station name. Should not be nil.
 *  @param withCrossfade if true, if crossfading is enabled, and if music is currenty
 *    playing, the currently playing song will fade into the song in the new station
 *    as soon as it is loaded.
 *
 *  @return true if a station with the given name is found
 *  @see activeStation
 */

- (BOOL) setActiveStationByName: (nonnull NSString *)name withCrossfade: (BOOL) withCrossfade DEPRECATED_ATTRIBUTE;

/**
 * @deprecated Clients should find FMStation references by pulling them from
 * stationList, localOfflineStationList, or remoteOfflineStationList.
 *
 * Search through the list of available stations, and return the one that has
 * an option attribute named 'key' with a string value of 'value'.
 *
 * @param key name of attribute to inspect
 * @param value attribute value that matching station should contain
 */

- (nullable FMStation *) getStationWithOptionKey:  (nonnull NSString *) key Value: (nonnull NSObject *) value DEPRECATED_ATTRIBUTE;

/**
 * @deprected This method is called internally now and clients need not call it.
 *
 * @param stations list of stations to prepare
 */
- (void)prepareStations:(nullable NSArray<FMStation *> *) stations DEPRECATED_ATTRIBUTE;

/**
 * @deprecated Clients should look for the FMAudioPlayerMusicQueuedNotification
 * notification to know when music is queued up in the player, rather than
 * rely on this property, which will be removed in the next major version.
 *
 * Indicates if the SDK has retrieved the next song for playback from the
 * server and is ready to start playing it.
 */
@property (nonatomic, readonly) BOOL isPreparedToPlay DEPRECATED_ATTRIBUTE;

/**
 @deprecated local detection is no longer performed by this library
 
 This call to initialize the library and then detect whether the user had any local
 music available for playback.
 
 @param token public authentication token. Use `@"demo"` during testing/development.
 @param secret private authentication token. Use `@"demo"` during testing/development.
 @param detectLocalMusic when true, the user's local media collection will be queried to
 sample what type of music they listen to
 */

+ (void)setClientToken:(nonnull NSString *)token secret:(nonnull NSString *)secret detectLocalMusic:(BOOL) detectLocalMusic DEPRECATED_ATTRIBUTE;





@end
