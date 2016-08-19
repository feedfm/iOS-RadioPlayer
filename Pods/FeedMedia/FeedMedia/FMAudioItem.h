//
//  FMAudioItem.h
//  sdktest
//
//  Created by James Anthony on 3/7/13.
//  Copyright (c) 2013 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  Represents audio track
 */
@interface FMAudioItem : NSObject

/**
 *  Track identifier. Two FMAudioItem objects treated as equal if their playId properties are equal.
 */
@property (readonly) NSString *playId;
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
 *  Track duration in seconds
 */
@property (readonly) NSTimeInterval duration;
/**
 *  Track file URL
 */
@property (readonly) NSURL *contentUrl;
/**
 *  Codec used to encode track. For example: "he-aac"
 */
@property (readonly) NSString *codec;
/**
 *  Average track bitrate in Kbps
 */
@property (readonly) double bitrate;
/**
 *  If track is liked
 */
@property (readonly) BOOL liked;
/**
 *  If track is disliked
 */
@property (readonly) BOOL disliked;

/**
 *  Creates FMAudioItem from the JSON provided
 *
 *  @param jsonDictionary JSON dictionary
 *
 *  @return returns new FMAudioItem instance
 */
- (id)initWithJSON:(id)jsonDictionary;

/**
 *  Assigns corresponding values to <liked> and <disliked> properties
 */
- (void)like;
/**
 *  Assigns corresponding values to <liked> and <disliked> properties
 */
- (void)dislike;
/**
 *  Assigns corresponding values to <liked> and <disliked> properties
 */
- (void)unlike;

@end