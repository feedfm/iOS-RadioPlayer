//
//  FMPlayerViewController.h
//
//  Created by Eric Lambrecht on 6/22/16.
//  Copyright © 2016 Feed Media All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FMPlayerViewController : UIViewController

@property (strong, nonatomic) NSArray *visibleStationNames;
@property (strong, nonatomic) NSArray *unhiddenStationNames;
@property (strong, nonatomic) NSString *defaultStationName;

@end
