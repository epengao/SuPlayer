//
//  MediaFileTableViewController.m
//  SuPlayer
//
//  Created by Kortide on 15/11/4.
//  Copyright © 2015年 EC. All rights reserved.
//

#import "VideoCell.h"
#import <MediaEngine/MediaEngine.h>
#include "PlayVideoViewController.h"
#import "MediaFileTableViewController.h"


@interface MediaFileTableViewController ()
{
    NSArray *videoFileList;
    NSString *videoFilePath;
}
@property (nonatomic, strong)MediaEngine *mediaEngine;
@end

@implementation MediaFileTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    [self getVideoFileList];
    [self.tableView reloadData];
    self.mediaEngine = [MediaEngine sharedMediaEngine];
}

- (void)dealloc
{
    if(self.mediaEngine)
    {
        [MediaEngine DestoryMediaEngine:self.mediaEngine];
        self.mediaEngine = nil;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - Get all the file list
- (void) getVideoFileList
{
    NSArray *patchs = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [patchs objectAtIndex:0];
    NSString *fileDirectory = [documentsDirectory stringByAppendingPathComponent:@""];
    videoFilePath = fileDirectory;
    videoFileList = [[NSFileManager defaultManager] subpathsOfDirectoryAtPath:fileDirectory error:nil];
}
    
#pragma mark - Table view delegate
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return videoFileList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    VideoFileCell *cell = (VideoFileCell *)[tableView dequeueReusableCellWithIdentifier:@"reuseCell"];
    if (cell == nil) {
        cell = [[VideoFileCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseCell"];
    }
    [cell setCellContent:videoFilePath withFileName:videoFileList[indexPath.row]];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    PlayVideoViewController *playView = [[PlayVideoViewController alloc]init];
    playView.videoFileName = [NSString stringWithFormat:@"%@/%@", videoFilePath, videoFileList[indexPath.row]];
    [self presentViewController:playView animated:YES completion:nil];
}

@end
