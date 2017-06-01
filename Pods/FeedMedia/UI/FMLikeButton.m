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
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playLikeStatusUpdated:) name:FMAudioPlayerLikeStatusChangeNotification object:_feedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerUpdated:) name:FMAudioPlayerCurrentItemDidBeginPlaybackNotification object:self.feedPlayer];
    
    [self addTarget:self action:@selector(onLikeClick) forControlEvents:UIControlEventTouchUpInside];
    ;

    [self updateButtonState];
    
}

- (void) setImage:(UIImage *)image forState:(UIControlState)state {
    [super setImage:image forState:state];
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) setAudioItem:(FMAudioItem *)audioItem {
    _audioItem = audioItem;
    
    [self updateButtonState];
}

- (void) onLikeClick {
    FMAudioItem *ai = (_audioItem == nil) ? _feedPlayer.currentItem : _audioItem;

    if (ai.liked) {
        [_feedPlayer unlikeAudioItem:ai];
    } else {
        [_feedPlayer likeAudioItem:ai];
    }
    
    [self updateButtonState];
}

- (void) playLikeStatusUpdated: (NSNotification *)notification {
    FMAudioItem *notificationAudioItem = notification.userInfo[FMAudioItemKey];
    
    FMAudioItem *ai = (_audioItem == nil) ? _feedPlayer.currentItem : _audioItem;
    
    if ([ai isEqual:notificationAudioItem]) {
        [self updateButtonState];
    }
}

- (void) playerUpdated: (NSNotification *)notification {
    if (_audioItem == nil) {
        [self updateButtonState];
    }
}

- (void) updateButtonState {
    if (_audioItem != nil) {
        self.enabled = YES;
        self.selected = _audioItem.liked;

    } else {
        FMAudioPlayerPlaybackState newState = _feedPlayer.playbackState;
        BOOL liked = _feedPlayer.currentItem.liked;
        
        switch (newState) {
            case FMAudioPlayerPlaybackStatePaused:
            case FMAudioPlayerPlaybackStatePlaying:
            case FMAudioPlayerPlaybackStateStalled:
            case FMAudioPlayerPlaybackStateRequestingSkip:
                self.enabled = YES;
                self.selected = liked;
                break;
            case FMAudioPlayerPlaybackStateReadyToPlay:
            case FMAudioPlayerPlaybackStateWaitingForItem:
            case FMAudioPlayerPlaybackStateComplete:
            case FMAudioPlayerPlaybackStateUnavailable:
            case FMAudioPlayerPlaybackStateUninitialized:
                self.enabled = NO;
                self.selected = NO;
        }
    }
}

#endif

@end
