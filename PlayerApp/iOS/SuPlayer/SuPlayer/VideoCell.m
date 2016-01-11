//
//  MovieListCell.m
//  SuPlayer
//
//  Created by Kortide on 15/11/4.
//  Copyright © 2015年 EC. All rights reserved.
//

#import "VideoCell.h"
#import <AVFoundation/AVFoundation.h>

@interface VideoFileCell ()
@property (weak, nonatomic) IBOutlet UILabel *fileName;
@property (weak, nonatomic) IBOutlet UIImageView *thumbnail;
@end


@implementation VideoFileCell

- (void)awakeFromNib {
    float w = [UIScreen mainScreen].bounds.size.width;
    UIView *endLine = [[UIView alloc]initWithFrame:CGRectMake(0, self.bounds.size.height-1, w, 1)];
    [endLine setBackgroundColor:[UIColor grayColor]];
    [self addSubview:endLine];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
}

- (void)setCellContent: (NSString*)filePath withFileName:(NSString*)fileName
{
    self.fileName.text = fileName;

    NSString *file = [NSString stringWithFormat:@"%@/%@", filePath, fileName];
    UIImage *thumbnail = [self thumbnailImageForVideo:file];
    if(thumbnail)
        self.thumbnail.image = thumbnail;
    else
        self.thumbnail.image = [UIImage imageNamed:@"test"];
    
    UIImageView *playIcon = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"play"]];
    playIcon.center = self.thumbnail.center;
    [self.thumbnail addSubview:playIcon];
}

- (UIImage *)thumbnailImageForVideo:(NSString *)videoFile
{
    AVURLAsset *asset = [[AVURLAsset alloc] initWithURL:[NSURL fileURLWithPath:videoFile] options:nil];
    AVAssetImageGenerator *gen = [[AVAssetImageGenerator alloc] initWithAsset:asset];
    gen.appliesPreferredTrackTransform = YES;
    CMTime time = CMTimeMakeWithSeconds(0.0, 600);
    NSError *error = nil;
    CMTime actualTime;
    CGImageRef image = [gen copyCGImageAtTime:time actualTime:&actualTime error:&error];
    UIImage *thumb = [[UIImage alloc] initWithCGImage:image];
    CGImageRelease(image);
    return thumb;
}

@end
