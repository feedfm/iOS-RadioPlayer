//
//  FMMetadataLabel.m
//  iOS-UI-SDK

//
//  Created by Eric Lambrecht on 4/27/15.
//  Copyright (c) 2015 Feed Media. All rights reserved.
//

#import "FMMetadataLabel.h"

@interface FMMetadataLabel ()

#if !TARGET_INTERFACE_BUILDER
@property (strong, nonatomic) FMAudioPlayer *feedPlayer;
#endif

@end

@implementation FMMetadataLabel

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
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songUpdated:) name:FMAudioPlayerCurrentItemDidBeginPlaybackNotification object:self.feedPlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stateChanged:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:self.feedPlayer];
    
    [self updateText];
}

- (void) setText: (NSString *) text{
    // when running live, only we get to set the text
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    // When created from nib, the 'text' attribute might be set without
    // going through our overridden 'setText' method (!!). Let's override
    // that here:
    [self updateText];
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) songUpdated: (NSNotification *) notification {
    [self updateText];
}

- (void) stateChanged: (NSNotification *) notification {
    // we only update the displayed text if the player transitions
    // to idle or complete
    FMAudioPlayerPlaybackState state = [_feedPlayer playbackState];
    
    if ((state == FMAudioPlayerPlaybackStateComplete) ||
        (state == FMAudioPlayerPlaybackStateReadyToPlay)) {
        [self updateToBlankText];
    }
}

- (void) updateToBlankText {
    super.text = @"";
}

- (void) updateText {
    FMAudioItem *current = [_feedPlayer currentItem];
    
    if (!current || !_format || (_format.length == 0)) {
        super.text = @"";
        return;
    }
    
    // swap %ARTIST with artist name, %TRACK with track name, %ALBUM with album name
    NSMutableString *string = [NSMutableString stringWithString:_format];
    
    [string replaceOccurrencesOfString:@"%ARTIST" withString:current.artist options:NSLiteralSearch range:NSMakeRange(0, [string length])];

    [string replaceOccurrencesOfString:@"%TRACK" withString:current.name options:NSLiteralSearch range:NSMakeRange(0, [string length])];
    
    [string replaceOccurrencesOfString:@"%ALBUM" withString:current.album options:NSLiteralSearch range:NSMakeRange(0, [string length])];
    
    super.text = string;

#if TARGET_OS_TV
#else
    self.marqueeType = MLContinuous;
#endif

}

#endif

- (void) setFormat:(NSString *)format {
    _format = format;

#if !TARGET_INTERFACE_BUILDER
    [self updateText];
#else
    [super setText:_format];
#endif
}

@end
