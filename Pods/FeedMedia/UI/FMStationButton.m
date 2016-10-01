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
    
    [self addTarget:self action:@selector(onClick) forControlEvents:UIControlEventTouchUpInside];
    
    [self updatePlayerState];
}

- (void) stationUpdated: (NSNotification *)notification {
    [self updatePlayerState];
}

- (void) onClick {
    [_feedPlayer setActiveStationByName:_stationName];
    
    if (_playOnClick) {
        [_feedPlayer play];
    }
}

- (void) setStationName:(NSString *)stationName {
    _stationName = stationName;
    
    [self updatePlayerState];
}

- (void) updatePlayerState {
    if ([_feedPlayer.activeStation.name isEqualToString:_stationName]) {
        [self setSelected:YES];
        
    } else {
        [self setSelected:NO];
        
    }
}

#endif

@end
