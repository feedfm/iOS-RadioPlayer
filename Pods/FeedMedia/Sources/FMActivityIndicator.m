//
//  FMActivityIndicator.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/11/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMActivityIndicator.h"

#if !TARGET_INTERFACE_BUILDER

@interface FMActivityIndicator ()

@property (strong, nonatomic) FMAudioPlayer *feedPlayer;

@end

#endif

@implementation FMActivityIndicator

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

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:_feedPlayer];
    
    [self updatePlayerState];
    
}

- (void) playerUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    FMAudioPlayerPlaybackState newState;
    
    newState = _feedPlayer.playbackState;

    switch (newState) {
        case FMAudioPlayerPlaybackStateOfflineOnly:
        case FMAudioPlayerPlaybackStateReadyToPlay:
        case FMAudioPlayerPlaybackStatePaused:
        case FMAudioPlayerPlaybackStatePlaying:
        case FMAudioPlayerPlaybackStateComplete:
        case FMAudioPlayerPlaybackStateUnavailable:
        case FMAudioPlayerPlaybackStateUninitialized:
            [self stopAnimating];
            break;

        case FMAudioPlayerPlaybackStateWaitingForItem:
        case FMAudioPlayerPlaybackStateStalled:
        case FMAudioPlayerPlaybackStateRequestingSkip:
            [self startAnimating];
            break;
    }
}

#endif

@end
