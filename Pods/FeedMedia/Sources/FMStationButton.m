//
//  FMStationButton.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 5/14/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMStationButton.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-implementations"


@interface FMStationButton ()

#if !TARGET_INTERFACE_BUILDER
@property (strong, nonatomic) FMAudioPlayer *feedPlayer;
#endif

@end

@implementation FMStationButton

#if !TARGET_INTERFACE_BUILDER

- (id) initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self setup];
    }
    
    return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self setup];
    }
    
    return self;
}

- (id) init {
    if (self = [super init]) {
        [self setup];
    }
    
    return self;
}


- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) setup {
    _feedPlayer = [FMAudioPlayer sharedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stationUpdated:) name:FMAudioPlayerActiveStationDidChangeNotification object:_feedPlayer];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stateUpdated:) name:
     FMAudioPlayerPlaybackStateDidChangeNotification object:_feedPlayer];
    
    [self addTarget:self action:@selector(onClick) forControlEvents:UIControlEventTouchUpInside];
    
    [self updatePlayerState];
}

- (void) stationUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) stateUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) onClick {
    FMStation *currentStation = _feedPlayer.activeStation;
    
    if ([_station isEqual:currentStation]) {
        
        if (!_playOnClick) {
            return;
        }
        
        FMAudioPlayerPlaybackState state = _feedPlayer.playbackState;

        if ((state == FMAudioPlayerPlaybackStateComplete) ||
            (state == FMAudioPlayerPlaybackStateReadyToPlay) ||
            (state == FMAudioPlayerPlaybackStatePaused)) {
            [_feedPlayer play];
            
        } else {
            [_feedPlayer pause];
            
        }

    } else {
        [_feedPlayer setActiveStation:_station withCrossfade:_crossfade];
        
        if (_playOnClick) {
            [_feedPlayer play];
            
        }
    }
    
    [self updatePlayerState];

}

- (void) setStationName:(NSString *)stationName {

    if (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateUninitialized) {
        // just in case this was set before music was available
        [_feedPlayer whenAvailable:^{
            [self setStationName:stationName];
            
        } notAvailable:^{
            // nada
        }];
        return;
    }
    
    NSArray *stations = [[FMAudioPlayer sharedPlayer] stationList];
    
    for (FMStation *station in stations) {
        if ([station.name isEqualToString:stationName]) {
            _station = station;
            break;
        }
    }

    [self updatePlayerState];
}

- (NSString *)stationName {
    return _station.name;
}

- (void) setStation:(FMStation *)station {
    _station = station;
    
    [self updatePlayerState];
}

- (void) setPlayOnClick:(BOOL)playOnClick {
    _playOnClick = playOnClick;
    
    [self updatePlayerState];
}

- (void) setHideWhenActive:(BOOL)hideWhenActive {
    _hideWhenActive = hideWhenActive;
    
    [self updatePlayerState];
}

- (void) updatePlayerState {

    // disable player when we can't do playback
    if ((_feedPlayer.playbackState == FMAudioPlayerPlaybackStateUninitialized)
        || (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateUnavailable)) {
        self.enabled = NO;
        self.selected = NO;
        return;
    }
    
    self.enabled = YES;
    
    // if the station is active right now
    if ([_feedPlayer.activeStation isEqual:_station]
        && (_feedPlayer.playbackState != FMAudioPlayerPlaybackStateComplete)
        && (_feedPlayer.playbackState != FMAudioPlayerPlaybackStateReadyToPlay)) {

        if (_hideWhenActive) {
            self.hidden = YES;

        } else {
            self.hidden = NO;
            
            FMAudioPlayerPlaybackState newState = _feedPlayer.playbackState;
            
            // highlighted = YES = show the pause button
            // highlighted = NO = show the play button
            
            switch (newState) {
                case FMAudioPlayerPlaybackStateWaitingForItem:
                case FMAudioPlayerPlaybackStateStalled:
                case FMAudioPlayerPlaybackStateRequestingSkip:
                case FMAudioPlayerPlaybackStatePlaying:
                    [self setSelected:YES];

                    break;
                    
                case FMAudioPlayerPlaybackStateComplete:
                case FMAudioPlayerPlaybackStateReadyToPlay:
                case FMAudioPlayerPlaybackStatePaused:
                    [self setSelected:NO];

                    break;
                case FMAudioPlayerPlaybackStateOfflineOnly:
                case FMAudioPlayerPlaybackStateUninitialized:
                case FMAudioPlayerPlaybackStateUnavailable:
                    // shouldn't happen
                    break;
            }
            
        }

    } else {
        // station isn't active
        self.selected = NO;
        self.hidden = NO;
        
    }
}

#endif

@end

#pragma clang diagnostic pop
