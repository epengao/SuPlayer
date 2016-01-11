//
//  ViewController.m
//  iOS-TestPlayer
//
//  Created by GaoPeng on 15/10/15.
//  Copyright © 2015年 EC. All rights reserved.
//

#import "ViewController.h"
#import "MediaEngine/MediaEngine.h"


@interface ViewController () <MediaEngineDelegate>
{
    MediaEngine *me;
}
@property (weak, nonatomic) IBOutlet UIImageView *videoScreenView;
@property (weak, nonatomic) IBOutlet UISlider *progressBar;
@property (weak, nonatomic) MediaInfo* mediaInfo;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.videoScreenView.backgroundColor =  [UIColor blackColor];
    self.videoScreenView.contentMode = UIViewContentModeScaleAspectFit;
    if(nil == me)
    {
        me = [MediaEngine sharedMediaEngine:self.videoScreenView];
        me.delegate = self;
        NSString* docPath = [NSHomeDirectory() stringByAppendingPathComponent: @"Documents"];
        NSString* path = [NSString stringWithFormat: @"%@/%@", docPath, @"WZZ.mp4"];
        int ret = [me openMedia:path];
        if(ret == MediaEngine_Err_None)
            self.mediaInfo = [me getMediaInfo];
        else
        {
            NSLog(@"There is not such file:%@", path);
            [MediaEngine DestoryMediaEngine:me];
            me = nil;
        }
    }
}

- (IBAction)OpenMedia:(id)sender
{
    if(me)
    {
        NSString* docPath = [NSHomeDirectory() stringByAppendingPathComponent: @"Documents"];
        NSString* path = [NSString stringWithFormat: @"%@/%@", docPath, @"WZZ.mp4"];
        [me openMedia:path];
        
        self.mediaInfo = [me getMediaInfo];
    }
}

- (IBAction)PlayVideo:(id)sender
{
    if(me)
    {
        [me play];
    }
}

- (IBAction)PauseVideo:(id)sender
{
    if(me)
    {
        [me pause];
    }
}

- (IBAction)StopVideo:(id)sender
{
    if(me)
    {
        [me stop];
    }
}

- (IBAction)seekVideo:(UISlider*)sender
{
    NSUInteger duration = self.mediaInfo.nDuration;
    NSUInteger seekPos = sender.value/100 * duration;
    [me seek:seekPos];
}

- (IBAction)buttonSeek:(UIButton *)sender
{
    NSUInteger duration = self.mediaInfo.nDuration;
    NSUInteger seekPos = 0.5 * duration;
    [me seek:seekPos];
}

#pragma mark -- MediaEngDelegate
- (int)mediaStoped:(MediaEngine *)mediaEngine
{
    NSLog(@"mediaStoped.......");
    return 0;
}
- (int)seekCompleted:(MediaEngine *)mediaEngine
{
    NSLog(@"seekCompleted.......");
    return 0;
}

@end
