This is a demo iOS app that makes use of the Feed Media SDK
to power a Pandora-style Internet-radio app. The app 
shows how you can use station metadata to hide stations
and assign images and descriptive text to them.

This player will retrieve the list of stations do display
from the server and display or hide the station selector
accordingly. Background images for the music stations
are provided to the client along with station meta-data.
If background aren't provided by the server, there is a
default image provided in the FMPlayerAssets.xcassets file.

Check out our [Android version](https://github.com/feedfm/Android-RadioPlayer) as well!

*If you want to add a music player to your app with minimal
coding, see instructions below.*

!["tabbed station page"](images/tune.png)
!["music playing"](images/playing.png)
!["media controls"](images/mediabar.png)
!["lockscreen"](images/lockscreen.png)

# Add the player to your app

To add this music player to your app with minimal coding, follow
the steps below (note: we'll assume you're using CocoaPods):

- Add the [FeedMedia](https://cocoapods.org/?q=FeedMedia) and 
[SDWebImage](https://cocoapods.org/?q=sdwebimage) packages to your Podfile
and run `pod install` to add them to your project.

- Create a new `Player` group in your application.

- Open this repository's `iOS-RadioPlayer.xcworkspace` workspace,
  select all the files in the `iOS-RadioPlayer > Player` group, and
  drag and drop those files into the `Player` group in your
  application. Make sure to check the 'Copy Items if Needed' option.
  and make sure the files are added to your apps primary target.

- Open your app's AppDelegate and add a call to set your
  client token and secret:

```objective-c
#import <FeedMedia/FeedMedia.h>

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  //...
  
  [FMAudioPlayer setClientToken:@"demo" secret:@"demo"];
  
  //...
}
```

- Somewhere in your app you should place a button that will open the 
FeedMedia music player. Set the default visibility of that button to
"hidden", so that if the app can't contact Feed.fm or the user is outside
of the United States, the radio player won't be visible. Then add this
code to the ViewController to make the button visible when music is
available:

```objective-c
#import <FeedMedia/FeedMedia.h>

- (void)viewDidLoad {
  // ... 
  
  [[FMAudioPlayer sharedPlayer] whenAvailable:^{
    NSLog(@"music is available!");
        
    self.showPlayerButton.hidden = false;
        
  } notAvailable:^{
    NSLog(@"music is not available, so button will stay hidden");
        
  }];
  
  // ...
}
```

- Finally, attach the following `Touch Up Inside` event
handler to the button:

```objective-c
#import "FMPlayerViewController.h"
#import "FMResources.h"


- (IBAction) onPlayerButtonTouched {
  UIStoryboard *sb = [FMResources playerStoryboard];
  UINavigationController *vc = [sb instantiateViewControllerWithIdentifier:@"navigationViewController"];
  FMPlayerViewController *player = (FMPlayerViewController *) vc.topViewController;
  
  // if you want to change the title for the radio player:
  player.title = @"My Radio";
   
  [self presentViewController:vc animated:YES completion:nil];
}
```

- That's it! Music and stations can be added and removed server side, 
so there's no more touching required. Run your app and groove out! 

