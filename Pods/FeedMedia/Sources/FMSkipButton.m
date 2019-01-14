//
//  FMSkipButton.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMSkipButton.h"

#if !TARGET_INTERFACE_BUILDER

@interface FMSkipButton ()

@property (strong, nonatomic) FMAudioPlayer *feedPlayer;

@end

#endif

@implementation FMSkipButton

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
    
    NSNotificationCenter *ns = [NSNotificationCenter defaultCenter];
    [ns addObserver:self selector:@selector(onPlaybackStateDidChange:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:_feedPlayer];
    [ns addObserver:self selector:@selector(onCurrentItemDidChange:) name:FMAudioPlayerCurrentItemDidBeginPlaybackNotification object:_feedPlayer];
    [ns addObserver:self selector:@selector(onSkipDidFail:) name:FMAudioPlayerSkipFailedNotification object:_feedPlayer];
    [ns addObserver:self selector:@selector(onSkipStatusChanged:) name:FMAudioPlayerSkipStatusNotification object:_feedPlayer];
    
    [self addTarget:self action:@selector(onSkipClick) forControlEvents:UIControlEventTouchUpInside];
;
    
    [self updatePlayerState];
}

- (void) onSkipClick {
    [_feedPlayer skip];
}

- (void) onPlaybackStateDidChange: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) onCurrentItemDidChange: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    if (_feedPlayer.currentItem == nil) {
        [self setEnabled:NO];

    } else if (!_feedPlayer.canSkip) {
        [self setEnabled:NO];
        
    } else {
        FMAudioPlayerPlaybackState newState = _feedPlayer.playbackState;
    
        switch (newState) {
            case FMAudioPlayerPlaybackStateOfflineOnly:
            case FMAudioPlayerPlaybackStateUninitialized:
            case FMAudioPlayerPlaybackStateUnavailable:
            case FMAudioPlayerPlaybackStateRequestingSkip:
            case FMAudioPlayerPlaybackStateWaitingForItem:
            case FMAudioPlayerPlaybackStateComplete:
            case FMAudioPlayerPlaybackStateReadyToPlay:
                [self setEnabled:NO];
                break;
            case FMAudioPlayerPlaybackStatePaused:
            case FMAudioPlayerPlaybackStatePlaying:
            case FMAudioPlayerPlaybackStateStalled:
                [self setEnabled:YES];
                break;
        }
    }
}

- (void) onSkipDidFail: (NSNotification *)notification {
    [self setEnabled:NO];
}

- (void) onSkipStatusChanged: (NSNotification *)notification {
    [self updatePlayerState];
}


#endif

@end
