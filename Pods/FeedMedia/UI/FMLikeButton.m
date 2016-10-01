//
//  FMLikeButton.m
//  iOS-UI-SDK
//
//  Created by Eric Lambrecht on 3/10/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMLikeButton.h"
#import "FMAudioPlayer.h"

@interface FMLikeButton ()

@property (strong, nonatomic) FMAudioPlayer *feedPlayer;

@end

@implementation FMLikeButton

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

- (void) setup {
    

    _feedPlayer = [FMAudioPlayer sharedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:_feedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerLikeStatusChangeNotification object:_feedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerCurrentItemDidChangeNotification object:self.feedPlayer];
    
    [self addTarget:self action:@selector(onLikeClick) forControlEvents:UIControlEventTouchUpInside];
    ;

    [self updatePlayerState];
    
}

- (void) setImage:(UIImage *)image forState:(UIControlState)state {
    [super setImage:image forState:state];
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) onLikeClick {
    BOOL liked = _feedPlayer.currentItem.liked;

    if (liked) {
        [_feedPlayer unlike];
    } else {
        [_feedPlayer like];
    }
    
    [self updatePlayerState];
}

- (void) playerUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) updatePlayerState {
    FMAudioPlayerPlaybackState newState;
    BOOL liked;
    
    newState = _feedPlayer.playbackState;
    liked = _feedPlayer.currentItem.liked;

    
    switch (newState) {
        case FMAudioPlayerPlaybackStatePaused:
        case FMAudioPlayerPlaybackStatePlaying:
            self.enabled = YES;
            self.selected = liked;
            break;
        case FMAudioPlayerPlaybackStateStalled:
        case FMAudioPlayerPlaybackStateRequestingSkip:
            break;
        case FMAudioPlayerPlaybackStateReadyToPlay:
        case FMAudioPlayerPlaybackStateWaitingForItem:
        case FMAudioPlayerPlaybackStateComplete:
            self.enabled = NO;
            self.selected = NO;
    }
}

#endif

@end
