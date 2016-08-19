//
//  FMStation.h
//  sdktest
//
//  Created by James Anthony on 3/11/13.
//  Copyright (c) 2013 Feed Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Represents Radio Station
 */
@interface FMStation : NSObject <NSCopying>

/**
 *  Station name
 */
@property (readonly) NSString *name;
/**
 *  Station unique identifier
 */
@property (readonly) NSString *identifier;
/**
 *  Options dictionary
 */
@property (readonly) NSDictionary *options;

/**
 *  Initializer
 *
 *  @param jsonDictionary JSON dictionary
 *
 *  @return returns new FMStation instance
 */
- (id)initWithJSON:(id)jsonDictionary;

@end
