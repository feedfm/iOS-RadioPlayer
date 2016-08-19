//
//  FMDisclaimerViewController.m
//
//  Created by Eric Lambrecht on 6/22/16.
//  Copyright © 2016 Feed Media All rights reserved.
//

#import "FMDisclaimerViewController.h"

@interface FMDisclaimerViewController ()

@end

@implementation FMDisclaimerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)closePlayer:(id)sender {
    [[self presentingViewController] dismissViewControllerAnimated:YES completion:nil];
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
