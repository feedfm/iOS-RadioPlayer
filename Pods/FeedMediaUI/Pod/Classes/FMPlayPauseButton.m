//
//  FMPlayPauseButton.m
//  UITests
//
//  Created by Eric Lambrecht on 3/6/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FeedMedia/FMAudioPlayer.h"
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

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:_feedPlayer];
    
    [self addTarget:self action:@selector(onClick) forControlEvents:UIControlEventTouchUpInside];
    
    [self updatePlayerState];
}


- (void) onClick {
    if ((_feedPlayer.playbackState == FMAudioPlayerPlaybackStatePaused) ||
        (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateReadyToPlay) ||
        (_feedPlayer.playbackState == FMAudioPlayerPlaybackStateComplete)) {
        [_feedPlayer play];
    } else {
        [_feedPlayer pause];
    }
}

- (void) playerUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    FMAudioPlayerPlaybackState newState;

    newState = _feedPlayer.playbackState;

    // selected = YES = show the pause button
    // selected = NO = show the play button
    
    switch (newState) {
        case FMAudioPlayerPlaybackStateWaitingForItem:
            [self setSelected:YES];
            if (_hideWhenStalled) {
                [self setHidden:YES];
            }
            break;
        case FMAudioPlayerPlaybackStateReadyToPlay:
        case FMAudioPlayerPlaybackStatePaused:
            [self setSelected:NO];
            if (_hideWhenStalled) {
                [self setHidden:NO];
            }
            break;
        case FMAudioPlayerPlaybackStatePlaying:
            [self setSelected:YES];
            if (_hideWhenStalled) {
                [self setHidden:NO];
            }
            break;
        case FMAudioPlayerPlaybackStateStalled:
            [self setSelected:YES];
            if (_hideWhenStalled) {
                [self setHidden:YES];
            }
            break;
        case FMAudioPlayerPlaybackStateRequestingSkip:
            [self setSelected:YES];
            if (_hideWhenStalled) {
                [self setHidden:YES];
            }
            break;
        case FMAudioPlayerPlaybackStateComplete:
            [self setSelected:NO];
            if (_hideWhenStalled) {
                [self setHidden:NO];
            }
            break;
    }
    
    
}
#endif

@end
