//
//  FMPlayerViewController.m
//
//  Created by Eric Lambrecht on 6/22/16.
//  Copyright © 2016 Feed Media All rights reserved.
//

#import "FMPlayerViewController.h"
#import <FeedMedia/FeedMedia.h>
#import <FeedMedia/FeedMediaUI.h>
#import <SDWebImage/UIImageView+WebCache.h>

#define kStationRotationIntervalInSeconds 10
#define kMinimumStationRotationTimeInSeconds 2

#define kDEFAULT_BACKGROUND_IMAGE @"default_background"

@interface FMPlayerViewController ()

@property (weak, nonatomic) IBOutlet UIView *tuneInView;
@property (weak, nonatomic) IBOutlet UIView *tuningView;
@property (weak, nonatomic) IBOutlet UIView *playerControlsView;
@property (weak, nonatomic) IBOutlet UISegmentedControl *stationSelector;
@property (weak, nonatomic) IBOutlet UIImageView *backgroundView;
@property (weak, nonatomic) IBOutlet UILabel *descriptionLabel;

@property (strong, nonatomic) NSArray *visibleStations;
@property (nonatomic) NSInteger backgroundIndex;

@end

@implementation FMPlayerViewController {
    NSString *bgURL;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // figure out what stations to display
    [self calculateVisibleStations];

    // display available stations
    [self.stationSelector removeAllSegments];
    
    if ([self.visibleStations count] > 1) {
        [self.visibleStations enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            FMStation *station = obj;
        
            [self.stationSelector insertSegmentWithTitle:station.name atIndex:idx animated:false];
        }];

        // pick out which station we should be displaying off the bat
        int selectedStationIndex = [self calculateDefaultStation];
        self.stationSelector.selectedSegmentIndex = selectedStationIndex;

    } else {
        // remove station selector
        [self.stationSelector removeFromSuperview];

    }
    
    // update what we're displaying
    [self updateDisplay];

    // update when player state changes
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:self selector:@selector(onPlaybackStateChange:) name:FMAudioPlayerPlaybackStateDidChangeNotification object:[FMAudioPlayer sharedPlayer]];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [FMAudioPlayer sharedPlayer].disableSongStartNotifications = YES;
}

- (void)viewDidDisappear:(BOOL)animated {
    [FMAudioPlayer sharedPlayer].disableSongStartNotifications = NO;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];

    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    bgURL = nil;
}

/**
 * Return the station visible on the display
 */

- (FMStation *) visibleStation {
    int index = ([self.visibleStations count] == 1) ? 0 : (int) self.stationSelector.selectedSegmentIndex;
    
    FMStation *visibleStation = [self.visibleStations objectAtIndex: index];
    
    return visibleStation;
}

/**
 User wants to start music playback in some station
 */

- (IBAction) onUserClickedStart: (id) sender {
    // switch to the visible station, then start playback
    FMAudioPlayer *player = [FMAudioPlayer sharedPlayer];
    FMStation *activeStation = [player activeStation];
    FMStation *visibleStation = [self visibleStation];

    if (![activeStation isEqual:visibleStation]) {
        // change stations, if necessary
        player.activeStation = visibleStation;
    }
    
    // this will trigger player state update, which will lead to us redrawing
    // the UI
    [player play];
}

/**
 User selected different station for display
 */

- (IBAction) onUserSelectedStation: (id) sender {
    [self updateDisplay];
}

/**
 User wants to close player
 */

- (IBAction)closePlayer:(id)sender {
    [[self presentingViewController] dismissViewControllerAnimated:YES completion:nil];
}

/**
 State of player changed - so update display
 */

- (void)onPlaybackStateChange:(NSNotification *)notification {
    [self updateDisplay];
}

/**
 Based on the state of the music player and the station we're supposed
 to be looking at, display the proper things
 */

- (void) updateDisplay {
    FMAudioPlayer *player = [FMAudioPlayer sharedPlayer];
    FMAudioPlayerPlaybackState state = [player playbackState];
    FMStation *activeStation = [player activeStation];
    FMStation *visibleStation = [self visibleStation];
    
    // make sure background matches visible station
    NSString *bg = [self generateBackgroundImageURLForStation:visibleStation];
    if (bg == nil) {
        self.backgroundView.image = [UIImage imageNamed:kDEFAULT_BACKGROUND_IMAGE];
        [player setLockScreenImage:self.backgroundView.image];
        
        bgURL = nil;

    } else if (![bg isEqual:bgURL]) {
        [self.backgroundView sd_setImageWithURL:[NSURL URLWithString:bg]
                                      completed:^(UIImage * image, NSError *error, SDImageCacheType cacheType, NSURL *imageURL) {
                                          
                                          if (image == nil) {
                                              image = [UIImage imageNamed:kDEFAULT_BACKGROUND_IMAGE];
                                              self.backgroundView.image = image;
                                          }
                                          
                                          NSLog(@"updating lock screen to %@", bg);
                                          [player setLockScreenImage:image];
                                      }];
        bgURL = bg;
    }
    
    if (![visibleStation isEqual:activeStation] ||
        (state == FMAudioPlayerPlaybackStateReadyToPlay) ||
        (state == FMAudioPlayerPlaybackStateComplete)) {

        NSLog(@"Now displaying inactive or non-playing station %@", visibleStation.name);

        // set the description text
        if ((visibleStation.options != nil) &&
            (visibleStation.options[@"description"] != nil) &&
            [visibleStation.options[@"description"] isKindOfClass:[NSString class]]) {
            self.descriptionLabel.text = visibleStation.options[@"description"];
        } else {
            self.descriptionLabel.text = @"Tune in!";
        }
        
        // not displaying active station or not playing any music, so show 'tune in'
        self.tuneInView.hidden = FALSE;
        self.tuningView.hidden = TRUE;
        self.playerControlsView.hidden = TRUE;
        
    }  else if ((state == FMAudioPlayerPlaybackStateWaitingForItem) ||
                   (state == FMAudioPlayerPlaybackStateStalled)) {
        NSLog(@"Now displaying active, but stalled/waiting, station %@", visibleStation.name);
            
        // trying to play
        self.tuneInView.hidden = TRUE;
        self.tuningView.hidden = FALSE;
        self.playerControlsView.hidden = TRUE;
            
    } else {
        NSLog(@"Now displaying active playing station %@", visibleStation.name);
            
        // playing!
        self.tuneInView.hidden = TRUE;
        self.tuningView.hidden = TRUE;
        self.playerControlsView.hidden = FALSE;
        
    }
    
}

/**
 
 Look through the available list of stations that the server
 returned to us, and filter them based on the visibleStationNames
 and unhiddenStationNames arrays. Anything listed in visibleStationNames
 that is also available from the server gets displayed. If 
 visibleStationNames isn't specified, then anything available from
 the server is displayed as long as it isn't market as hidden or
 its name appears in the unhiddenStationNames array.

 */

- (void) calculateVisibleStations {
    NSArray *availableStations = [[FMAudioPlayer sharedPlayer] stationList];
    NSPredicate *filterPredicate;
    
    if (self.visibleStationNames) {
        // display all stations whose name appears in the visibleStationNames array
        filterPredicate = [NSPredicate predicateWithBlock:^BOOL(id  _Nonnull evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
            FMStation *station = (FMStation *) evaluatedObject;

            return [self.visibleStationNames containsObject: station.name];
        }];
        
    } else if (self.unhiddenStationNames) {
        // display all stations with no 'hidden:true' option and also any
        // hidden station listed in the unhiddenStationNames array
        filterPredicate = [NSPredicate predicateWithBlock:^BOOL(id  _Nonnull evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
            FMStation *station = (FMStation *) evaluatedObject;
            
            NSLog(@"working on station %@", station.name);
            
            BOOL hidden = ((station.options != nil) &&
                           (station.options[@"hidden"] != nil) &&
                           [station.options[@"hidden"] isKindOfClass:[NSNumber class]] &&
                           ([(NSNumber *) station.options[@"hidden"] boolValue] == YES));
            
            if (hidden) {
                NSLog(@"%@ is hidden", station.name);
                hidden = ![self.unhiddenStationNames containsObject: station.name];
            }
            
            return !hidden;
        }];
        
    } else {
        // display all stations with no 'hidden:true' option
        filterPredicate = [NSPredicate predicateWithBlock:^BOOL(id  _Nonnull evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
            FMStation *station = (FMStation *) evaluatedObject;
            
            return !((station.options != nil) &&
                     (station.options[@"hidden"] != nil) &&
                     [station.options[@"hidden"] isKindOfClass:[NSNumber class]] &&
                     ([(NSNumber *) station.options[@"hidden"] boolValue] == YES));
        }];

    }
    
    self.visibleStations = [availableStations filteredArrayUsingPredicate:filterPredicate];
}

/**
 
 Iterate through the list of visibleStations and return the index
 of the one that should be displayed by default. Priority is given
 to:
   - the station with the name defaultStationName
   - the station currently active
   - the first station
 
 */

- (int) calculateDefaultStation {
    FMStation *activeStation = [[FMAudioPlayer sharedPlayer] activeStation];
    __block int displayStationIndex = -1;
    __block int activeStationIndex = 0;
    
    [self.visibleStations enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        FMStation *station = obj;
        
        if ([station isEqual:activeStation]) {
            activeStationIndex = (int) idx;
        }
        
        if ([station.name isEqualToString:self.defaultStationName]) {
            displayStationIndex = (int) idx;
        }
    }];
    
    int selectedTab = (displayStationIndex > -1) ? displayStationIndex : activeStationIndex;
    
    NSLog(@"calculated default station index to be %d", selectedTab);

    return selectedTab;
}

#pragma mark Background image retrieval

/**
 This method returns the UIImage that should be displayed for the given
 station.
 */

- (NSString *) generateBackgroundImageURLForStation: (FMStation *) station {
    NSString *url = [station.options valueForKey:@"background_image_url"];
    
    return url;
}

@end
