//
//  FMTotalTimeLabel.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMTotalTimeLabel.h"

#define kFMProgressBarUpdateTimeInterval 0.5

#if !TARGET_INTERFACE_BUILDER

@interface FMTotalTimeLabel ()

@property (strong, nonatomic) FMAudioPlayer *feedPlayer;

@end

#endif


@implementation FMTotalTimeLabel

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

- (void) setText: (NSString *)text {
    // ignore
}

- (void) playerUpdated: (NSNotification *) notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    FMAudioPlayerPlaybackState newState = _feedPlayer.playbackState;
    
    switch (newState) {
        case FMAudioPlayerPlaybackStateWaitingForItem:
        case FMAudioPlayerPlaybackStateComplete:
        case FMAudioPlayerPlaybackStateReadyToPlay:
        case FMAudioPlayerPlaybackStateUnavailable:
        case FMAudioPlayerPlaybackStateUninitialized:
            [self resetProgress];
            break;
            
        case FMAudioPlayerPlaybackStatePaused:
        case FMAudioPlayerPlaybackStateRequestingSkip:
        case FMAudioPlayerPlaybackStatePlaying:
            [self updateProgress];
            break;
            
        default:
            // nada
            break;
    }
}

- (void)updateProgress {
    long duration = lroundf(_feedPlayer.currentItemDuration);
    
    if(duration > 0) {
        [super setText: [NSString stringWithFormat:@"%ld:%02ld", duration / 60, duration % 60]];
        
    }
    else {
        [super setText:@"0:00"];
    }
}

- (void)resetProgress {
    [super setText:_textForNoTime];
}

#endif

- (void) setTextForNoTime: (NSString *) theText {
    _textForNoTime = theText;

#if !TARGET_INTERFACE_BUILDER
    [self updatePlayerState];
#else
    [super setText:theText];
#endif
}



@end

#undef kFMProgressBarUpdateTimeInterval


