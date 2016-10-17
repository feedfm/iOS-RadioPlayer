//
//  FMResources.m
//  iOS-RadioPlayer
//
//  Created by Eric Lambrecht on 10/17/16.
//  Copyright © 2016 Eric Lambrecht. All rights reserved.
//

#import "FMResources.h"

@implementation FMResources

+ (UIStoryboard *)playerStoryboard {
    return [FMResources storyboardWithName:@"FMPlayerAndDisclaimer"];
}

+ (UIStoryboard *)storyboardWithName:(NSString *)name {
    return [UIStoryboard storyboardWithName:name bundle:[FMResources frameworkBundle]];
}

+ (NSBundle *)frameworkBundle {
    return [NSBundle bundleForClass:self.class];
}

+ (UIImage *)imageNamed:(NSString *)name {
    NSString *imagePath = [[FMResources frameworkBundle] pathForResource:name ofType:@"png"];
    return [UIImage imageWithContentsOfFile:imagePath];
}

@end
