//
//  FMPlayPauseButton.m
//  UITests
//
//  Created by Eric Lambrecht on 3/6/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMAudioPlayer.h"
#import "FMPlayPauseButton.h"

#if !TARGET_INTERFACE_BUILDER

@interface FMPlayPauseButton ()

@property (strong, nonatomic) FMAudioPlayer *feedPlayer;

@end

#endif

@implementation FMPlayPauseButton

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

- (void) setHideWhenStalled:(BOOL)hideWhenStalled {
    _hideWhenStalled = hideWhenStalled;
    
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

- (void) setHideWhenActive:(BOOL)hideWhenActive {
    _hideWhenActive = hideWhenActive;
    
    [self updatePlayerState];
}


- (void) onClick {
    if (_station) {
        FMStation *currentStation = _feedPlayer.activeStation;
        
        if (![_station isEqual:currentStation]) {
            [_feedPlayer setActiveStation:_station withCrossfade:_crossfade];
            [_feedPlayer play];
            
            return;
        }
    }
    
    if ((_feedPlayer.playbackState == FMAudioPlayerPlaybackStatePaused) ||
        (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateReadyToPlay) ||
        (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateComplete)) {

        [_feedPlayer play];
    } else {
        [_feedPlayer pause];
    }
}

- (void) stationUpdated: (NSNotification *)notification {
    if (_station) {
        [self updatePlayerState];
    }
}
- (void) stateUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    if (_station) {
        if (![_feedPlayer.activeStation isEqual:_station]
            || (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateComplete)
            || (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateReadyToPlay)) {
            // station isn't active
            self.selected = NO;
            self.enabled = YES;
            self.hidden = NO;
            
            return;

        } else if (_hideWhenActive) {
            self.hidden = YES;
            
            return;
        }
    }
    
    FMAudioPlayerPlaybackState newState = _feedPlayer.playbackState;

    switch (newState) {
        case FMAudioPlayerPlaybackStateWaitingForItem:
        case FMAudioPlayerPlaybackStateStalled:
        case FMAudioPlayerPlaybackStateRequestingSkip:
            [self setSelected:YES];
            [self setEnabled:YES];
            [self setHidden:_hideWhenStalled];
            break;

        case FMAudioPlayerPlaybackStateComplete:
        case FMAudioPlayerPlaybackStateReadyToPlay:
        case FMAudioPlayerPlaybackStatePaused:
            [self setSelected:NO];
            [self setEnabled:YES];
            [self setHidden:NO];
            break;

        case FMAudioPlayerPlaybackStatePlaying:
            [self setSelected:YES];
            [self setEnabled:YES];
            [self setHidden:NO];
            break;
            
        case FMAudioPlayerPlaybackStateUninitialized:
        case FMAudioPlayerPlaybackStateUnavailable:
            [self setSelected:NO];
            [self setEnabled:NO];
            [self setHidden:NO];
            break;
    }
    
    
}
#endif

@end
