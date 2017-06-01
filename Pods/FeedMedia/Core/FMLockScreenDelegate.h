//
//  FMLockScreenDelegate.h
//  FeedMediaCore
//
//  Created by Eric Lambrecht on 4/18/17.
//  Copyright © 2017 Feed Media. All rights reserved.
//

#ifndef FMLockScreenDelegate_h
#define FMLockScreenDelegate_h

/**
 If you don't want the Feedfm SDK to fully manage lock screen metadata
 and the display of feedback command buttons, then pass the FMAudioPlayer an
 FMLockScreenDelegate. When the FMAudioPlayer wants to update the lock screen 
 it will, instead, call this delegate, which is expected to update the 
 MPNowPlayingInfoCenter data and enable or disable the like, dislike, and skip 
 buttons.
 
 Note that, unless you set the FMAudioPlayer's doesHandleRemoteCommands
 property to FALSE, the SDK will still register to handle skip, like, dislike,
 play, and pause MPRemoteCommand events.
 
 */

@protocol FMLockScreenDelegate<NSObject>

/**
 This method is called when the Feedfm SDK wishes to update the
 MPNowPlayingInfoCenter metadata. 
 
 The dictionary passed in is suitable
 for assignment to [MPNowPlayingInfoCenter defaultCenter].nowPlayingInfo
 and may contain data for the following keys:

 - MPMediaItemPropertyAlbumTitle
 - MPMediaItemPropertyArtist
 - MPMediaItemPropertyTitle
 - MPMediaItemPropertyPlaybackDuration
 - MPNowPlayingInfoPropertyElapsedPlaybackTime
 - MPNowPlayingInfoPropertyPlaybackRate
 - MPMediaItemPropertyArtwork
 
 note that these keys may be missing if no song is playing
 
 ** NOTE ** all apps powered by the Feed.fm SDK _must_ display song
 title, artist, and album information on the lock screen, per
 our music licenses.
 
 To exactly duplicate the default handling of the MPNowPlayingInfoCenter
 data by the Feedfm SDK, you would implement this method as:
 
    [MPNowPlayingInfoCenter defaultCenter].nowPlayingInfo = info;
 
    MPRemoteCommandCenter *rcc = [MPRemoteCommandCenter sharedCommandCenter];

    MPRemoteCommand *nextTrackCommand = [rcc nextTrackCommand];
    MPFeedbackCommand *dislikeCommand = [rcc dislikeCommand];
    MPFeedbackCommand *likeCommand = [rcc likeCommand];

    if ([info objectForKey:MPMediaItemPropertyTitle] != NULL) {
        [nextTrackCommand setEnabled: nextTrackEnabled];
 
        [dislikeCommand setEnabled:YES];
        [dislikeCommand setActive:dislikeActive];
 
        [likeCommand setEnabled:YES];
        [likeCommand setActive:likeActive];

    } else {
        [nextTrackCommand setEnabled: NO];
        [dislikeCommand setEnabled:NO];
        [likeCommand setEnabled:NO];
 
    }
 
 @param info an NSDictionary suitable for assigning to the MPNowPlayingInfoCenter's nowPlayingInfo property
 @param dislikeActive when TRUE, the user dislikes the currently playing song
 @param likeActive when TRUE, the user likes the currently playing song
 @param nextTrackEnabled when TRUE, the user may skip the currently playing song
 
 */

 - (void) updateLockScreenInfo: (NSDictionary *) info
                 dislikeActive: (BOOL) dislikeActive
                    likeActive: (BOOL) likeActive
              nextTrackEnabled: (BOOL) nextTrackEnabled;

@end

#endif /* FMLockScreenDelegate_h */
