//
//  FMStationButton.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 5/14/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMAudioPlayer.h"
#import "FMStationButton.h"

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
    [_feedPlayer setActiveStation:_station];
    
    if (_playOnClick) {
        [_feedPlayer play];
        
        // the state update notification is kind of slow, so we
        // update the state of the button here so things are a
        // little more responsive for the user
        if (_hideWhenActive) {
            self.hidden = YES;
        } else {
            self.enabled = YES;
            self.selected = YES;
        }
    }
}

- (void) setStationName:(NSString *)stationName {
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

- (void) updatePlayerState {

    // disable player when we can't do playback
    if ((_feedPlayer.playbackState == FMAudioPlayerPlaybackStateUninitialized)
        || (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateUnavailable)) {
        self.enabled = NO;

    // select or hide when active station matches this button
    } else if ([_feedPlayer.activeStation isEqual:_station]
               && (_feedPlayer.playbackState != FMAudioPlayerPlaybackStateComplete)
               && (_feedPlayer.playbackState != FMAudioPlayerPlaybackStateReadyToPlay)) {
        if (_hideWhenActive) {
            self.hidden = YES;
        } else {
            self.enabled = YES;
            self.selected = YES;
        }

    // enabled and not selected and not hidden when this station is not active or is idle
    } else {
        self.enabled = YES;
        self.hidden = NO;
        self.selected = NO;
        
    }
}

#endif

@end
