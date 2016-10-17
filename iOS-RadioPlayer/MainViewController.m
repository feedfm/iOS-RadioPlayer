//
//  ViewController.m
//
//  Created by Eric Lambrecht on 6/22/16.
//  Copyright © 2016 Feed Media All rights reserved.
//

#import "MainViewController.h"
#import "FMPlayerViewController.h"
#import "FMResources.h"
#import <FeedMedia/FeedMedia.h>

@interface MainViewController ()

@property (weak, nonatomic) IBOutlet UIButton *openDefaultButton;
@property (weak, nonatomic) IBOutlet UIButton *openDefaultAndPromoButton;
@property (weak, nonatomic) IBOutlet UIButton *openPromoButton;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[FMAudioPlayer sharedPlayer] whenAvailable:^{
        NSLog(@"music is available!");
        
        self.openDefaultButton.hidden = false;
        self.openDefaultAndPromoButton.hidden = false;
        self.openPromoButton.hidden = false;

        [[FMAudioPlayer sharedPlayer] prepareToPlay];
        
    } notAvailable:^{
        NSLog(@"music is not available");
        
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(IBAction) didClickPresentDefault: (id) sender {
    UIStoryboard *sb = [FMResources playerStoryboard];
    UINavigationController *vc = [sb instantiateViewControllerWithIdentifier:@"navigationViewController"];
    FMPlayerViewController *player = (FMPlayerViewController *) vc.topViewController;
    
    player.title = @"My Radio";
    
    [self presentViewController:vc animated:YES completion:nil];
}

-(IBAction) didClickPresentDefaultAndHidden: (id) sender {
    UIStoryboard *sb = [FMResources playerStoryboard];
    UINavigationController *vc = [sb instantiateViewControllerWithIdentifier:@"navigationViewController"];
    FMPlayerViewController *player = (FMPlayerViewController *) vc.topViewController;
    
    player.title = @"My Radio";
    player.unhiddenStationNames = @[ @"Hidden Station" ];
    
    [self presentViewController:vc animated:YES completion:nil];
}

-(IBAction) didClickPresentHidden: (id) sender {
    UIStoryboard *sb = [FMResources playerStoryboard];
    UINavigationController *vc = [sb instantiateViewControllerWithIdentifier:@"navigationViewController"];
    FMPlayerViewController *player = (FMPlayerViewController *) vc.topViewController;
    
    player.title = @"My Radio";
    player.visibleStationNames = @[ @"Hidden Station" ];
    
    [self presentViewController:vc animated:YES completion:nil];
}



-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender{

    // "presentDefault" segue replicates default behavior of showing all not hidden stations
    
    if([segue.identifier isEqualToString:@"presentDefaultAndHidden"]){
        // show default stations plus unhide the "Hidden" station
        UINavigationController *navController = (UINavigationController *)segue.destinationViewController;
        FMPlayerViewController *controller = (FMPlayerViewController *)navController.topViewController;
        
        controller.unhiddenStationNames = @[ @"Hidden Station" ];
        
        NSLog(@"showing default plus hidden station");

    } else if ([segue.identifier isEqualToString:@"presentHidden"]) {
        // just show the "Hidden" station
        UINavigationController *navController = (UINavigationController *)segue.destinationViewController;
        FMPlayerViewController *controller = (FMPlayerViewController *)navController.topViewController;
        
        controller.visibleStationNames = @[ @"Hidden Station" ];

        NSLog(@"showing hidden station");
    }
}

@end
