//
//  FMAudioItem.h
//  sdktest
//
//  Created by James Anthony on 3/7/13.
//  Copyright (c) 2013-2016 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "FMStation.h"


/**
 * Represents an audio track. Instances of this become available via the `[FMAudioPlayer currentItem]`
 * property.
 */
@interface FMAudioItem : NSObject <NSCopying>

/*
 *  Track identifier.
 */
@property NSString *playId;

/*
 * Audio File identifier.
 */
@property (readonly) NSString *id;

/**
 *  Track name
 */
@property (readonly) NSString *name;
/**
 *  Artist
 */
@property (readonly) NSString *artist;
/**
 *  Album
 */
@property (readonly) NSString *album;

/**
 * Station the play was created from
 */
@property FMStation *station;

/*
 * A name for this audio file that should be displayed in
 * place of name/artist/album (used for non-song audio files,
 * such as ads or introductions)
 */
@property (readonly) NSString *displayName;

/**
 * Arbitrary metadata attached to this song
 */
@property (readonly) NSDictionary *metadata;

/**
 *  Track duration in seconds
 */
@property (readonly) NSTimeInterval duration;
/*
 *  Track file URL
 */
@property NSURL *contentUrl;
/*
 *  Codec used to encode track. For example: "he-aac"
 */
@property (readonly) NSString *codec;
/*
 *  Average track bitrate in Kbps
 */
@property (readonly) double bitrate;

/*
 * When trimming audio, start playback at this
 * point.
 */
@property (readonly) CMTime trimStart;

/*
 * When trimming audio, end playback at this
 * point.
 */
@property (readonly) CMTime trimEnd;

/**
 *  If track is liked
 */
@property (readonly) BOOL liked;
/**
 *  If track is disliked
 */
@property (readonly) BOOL disliked;

/**
 * Used internally to keep perceived volume levels equal
 */

@property (readonly) double replayGain;

/**
 * Used internally to pre-boost the volume of this song
 */

@property double preGain;

/**
 *  Creates FMAudioItem from the JSON provided. 
 *
 *  @param jsonDictionary JSON dictionary
 *
 *  @return returns new FMAudioItem instance
 */
- (id)initWithJSON:(id)jsonDictionary;

/**
 *  Creates FMAudioItem from the JSON and station provided.
 *
 *  @param jsonDictionary JSON dictionary
 *  @param station FMStation that the play was created in
 *
 *  @return returns new FMAudioItem instance
 */

- (id)initWithJSON:(id)jsonDictionary station:(FMStation *)station;

/*
 *  Assigns corresponding values to <liked> and <disliked> properties. Note, this
 *  is for internal use, and shouldn't be used to respond to user input -
 *  use the `[FMAudioPlayer like]` method instead.
 */
- (void)like;

/*
 *  Assigns corresponding values to <liked> and <disliked> properties. Note, this
 *  is for internal use, and shouldn't be used to respond to user input -
 *  use the `[FMAudioPlayer dislike]` method instead.

 */
- (void)dislike;

/*
 *  Assigns corresponding values to <liked> and <disliked> properties. Note, this
 *  is for internal use, and shouldn't be used to respond to user input -
 *  use the `[FMAudioPlayer unlike]` method instead.

 */
- (void)unlike;

@end
