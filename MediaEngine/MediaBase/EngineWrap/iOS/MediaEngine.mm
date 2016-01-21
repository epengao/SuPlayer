/*
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
* Copyright (C) 2014-2016 Gao Peng

* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.

* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.

* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the Free
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

* ---------------------------------------------------------------------
* MediaEngineWrap.mm
*
* This file for MediaEngine APIs implementation for iOS platform.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#import "MediaEngine.h"
#import "MediaCommon.h"
#import "MediaEngineWrap.h"


@implementation MediaInfo
- (id)init
{
    self = [super init];
    if(self)
    {
        self.nWidth = 0;
        self.nHeight = 0;
        self.nDuration = 0;
        self.nAudioDuration = 0;
        self.nVideoDuration = 0;
    }
    return self;
}
@end

@interface MediaEngine ()
{
    NSTimer *timer;
    MediaInfo *mediaInfo;
    MediaEngVideoScreen videoScreen;
    MediaEngHandle mediaEngineHandle;
}
@end

int NotifyHandler(void* pUserData, int ID,
                  void* pParam1, void* pParam2);

@implementation MediaEngine

- (id)init
{
    if(self = [super init])
    {
        mediaInfo = nil;
        videoScreen.nWidth = 0;
        videoScreen.nHeight = 0;
        videoScreen.pScreen = NULL;
        InitMediaEngine(&mediaEngineHandle);
    }
    return self;
}

- (void)uninit
{
    mediaInfo = nil;
    UnInit(&mediaEngineHandle);
}

+ (MediaEngine *)sharedMediaEngine
{
    static MediaEngine *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[MediaEngine alloc]init];
    });
    
    return instance;
}

- (void)setVideoView: (UIImageView*)videoOutputView
{
    videoScreen.nWidth = 0x1;
    videoScreen.nHeight = 0x1;
    videoScreen.pScreen = (__bridge void*)videoOutputView;
}

- (int)openMedia:(NSString *)mediaPath
{
    if(!timer.valid)
    {
        [timer invalidate];
        timer = nil;
    }
    MediaEngNotify sNotify;
    sNotify.pUserData = (__bridge void*)self;
    sNotify.NotifyHandler = NotifyHandler;
    SetMediaNotify(mediaEngineHandle, &sNotify);
    return OpenMedia(mediaEngineHandle, [mediaPath UTF8String], &videoScreen);
}

- (void)play
{
    Play(mediaEngineHandle);
    timer = [NSTimer scheduledTimerWithTimeInterval:0.25 target:self selector:@selector(playbackTimeUpdate) userInfo:nil repeats:YES];
}

- (void)pause
{
    [timer invalidate];
    timer = nil;
    Pause(mediaEngineHandle);
}

- (void)seek:(NSUInteger)seekPos
{
    Seek(mediaEngineHandle, (unsigned int)seekPos);
}

- (void)stop
{
    [timer invalidate];
    timer = nil;
    mediaInfo = nil;
    Stop(mediaEngineHandle);
}

- (MediaEngineStatus)getMediaEngStatus
{
    MediaEngStatus status = MediaEngStatus_UnDefine;
    GetMediaEngineStatus(mediaEngineHandle, &status);
    return (MediaEngineStatus)status;
}

- (MediaInfo *)getMediaInfo
{
    if(mediaInfo == nil)
    {
        MediaEngMediaInfo engMediaInfo;
        GetMediaInfo(mediaEngineHandle, &engMediaInfo);

        mediaInfo = [[MediaInfo alloc] init];
        mediaInfo.nWidth = engMediaInfo.nWidth;
        mediaInfo.nHeight = engMediaInfo.nHeight;
        mediaInfo.nDuration = engMediaInfo.nDuration;
        mediaInfo.nAudioDuration = engMediaInfo.nAudioDuration;
        mediaInfo.nVideoDuration = engMediaInfo.nVideoDuration;
    }
    
    return mediaInfo;
}

- (NSUInteger)getPlayingPosition
{
    unsigned int pos = 0;
    GetPlayingPosition(mediaEngineHandle, &pos);
    return pos;
}

- (void)updateVideoOutputView:(UIImageView *)imageView;
{
    videoScreen.pScreen = (__bridge void*)imageView;
    UpdateVideoScreen(mediaEngineHandle, &videoScreen);
}

- (void)playbackTimeUpdate
{
    unsigned int pos = 0;
    GetPlayingPosition(mediaEngineHandle, &pos);
    if (self.delegate && [self.delegate respondsToSelector:@selector(playbackTimeUpdate:)])
    {
        [self.delegate playbackTimeUpdate:pos];
    }
}

+ (void)DestoryMediaEngine:(MediaEngine *)mediaEngine
{
    [mediaEngine uninit];
    mediaEngine = nil;
}

@end

int NotifyHandler(void* pUserData, int nID, void* pParam1, void* pParam2)
{
    int nRet = 0;
    MediaEngine *me = (__bridge MediaEngine*)pUserData;

    switch (nID)
    {
        case MediaEngNotify_PlayStarted:
        {
            if (me.delegate && [me.delegate respondsToSelector:@selector(playStarted)])
            {
                nRet = [me.delegate playStarted];
            }
            break;
        }
        case MediaEngNotify_MediaPaused:
        {
            if (me.delegate && [me.delegate respondsToSelector:@selector(mediaPaused)])
            {
                nRet = [me.delegate mediaPaused];
            }
            break;
        }
        case MediaEngNotify_MediaStoped:
        {
            if (me.delegate && [me.delegate respondsToSelector:@selector(mediaStoped)])
            {
                nRet = [me.delegate mediaStoped];
            }
            break;
        }
        case MediaEngNotify_SeekCompleted:
        {
            if (me.delegate && [me.delegate respondsToSelector:@selector(seekCompleted)])
            {
                nRet = [me.delegate seekCompleted];
            }
            break;
        }
        case MediaEngNotify_PlaybackFinished:
        {
            if (me.delegate && [me.delegate respondsToSelector:@selector(playbackFinished)])
            {
                nRet = [me.delegate playbackFinished];
            }
            break;
        }
        default:
            break;
    }

    return nRet;
}
