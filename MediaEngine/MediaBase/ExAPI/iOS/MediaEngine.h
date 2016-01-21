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
* MediaEngine.h
* This file MedianEngine APIs define.
* All APIs and other interface define for UI to desgine media player.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/* Return Err Define */
typedef NS_ENUM(NSUInteger, MediaEngineErrCode)
{
    MediaEngine_Err_None            = 0x00000000,
    MediaEngine_Err_InitErr         = 0x00000001,
    MediaEngine_Err_NotInit         = 0x00000002,
    MediaEngine_Err_FileNotSupport  = 0x00000003,
    MediaEngine_Err_VideoNotSupport = 0x00000004,
    MediaEngine_Err_AudioNotSupport = 0x00000005,
};

/* MediaEngine Play Status */
typedef NS_ENUM(NSUInteger, MediaEngineStatus)
{
    MediaEngineStatus_Inited      = 1,
    MediaEngineStatus_MediaOpend  = 2,
    MediaEngineStatus_Playing     = 3,
    MediaEngineStatus_Seeking     = 4,
    MediaEngineStatus_Pause       = 5,
    MediaEngineStatus_Stop        = 6,
    MediaEngineStatus_UnDefine    = 0xFFFF,
};

/* 
 * MeidaInfo
 * Note: duration use millisecond
 */
@interface MediaInfo : NSObject
  @property (nonatomic, assign) NSUInteger nWidth;
  @property (nonatomic, assign) NSUInteger nHeight;
  @property (nonatomic, assign) NSUInteger nDuration;
  @property (nonatomic, assign) NSUInteger nAudioDuration;
  @property (nonatomic, assign) NSUInteger nVideoDuration;
@end

/* MediaEngine delegate pre define */
@protocol MediaEngineDelegate;


/*
 * MediaEngine interface define.
 * This is a Singleton object of MediaEngine.
 */
@interface MediaEngine : NSObject

/*
 * delegate:
 * MediaEngine low layer message, or notify will be called to this delegate.
 */
@property (nonatomic, assign) id<MediaEngineDelegate> delegate;

/*
 * createMediaEngine: Create a new MediaEngine.
 * @return: MediaEngine* will be return if create successfully, else return NULL.
 */
+ (MediaEngine *)sharedMediaEngine;

/*
 * setVideoView: Set the video output image view.
 */
- (void)setVideoView:(UIImageView*)videoOutputView;

/*
 * penMedia: Open a local media file or network streaming that
 *            is specified by parameter mediaPath.
 * @ mediaPath: Media url of local media or network streaming. [UTF8String]
 * @ return: If open media sucessful return 0, else return error code.
 */
- (int)openMedia:(NSString *)mediaPath;

/*
 * play: Play current media specified by openMedia.
 */
- (void)play;

/*
 * pause: Pause current playing.
 */
- (void)pause;

/*
 * seek: Seek to a specified position of media content.
 * @ seekPos: Seek position, millisecond of the media duration.
 * NOTE: This is async call, return back immediately. After
 *       background thread finished it, seekCompleted of the 
 *       delegate will be called.
 */
- (void)seek:(NSUInteger)seekPos;

/*
 * stop: Stop current media content.
 */
- (void)stop;

/*
 * getMediaEngStatus: Get current MediaEngine status.
 * @ return: Current Engine status.
 */
- (MediaEngineStatus)getMediaEngStatus;

/*
 * getMediaInfo: Get the media content information.
 * @ return: Media content information.
 */
- (MediaInfo *)getMediaInfo;

/*
 * getPlayingPosition: Get current playing time position.
 * @ return: Current playing time position, millisecond.
 */
- (NSUInteger)getPlayingPosition;

/*
 * updateOutputVideoView: Set a new width and height, or a new video screen.
 * @ screen: New video screen.
 */
- (void)updateVideoOutputView:(UIImageView *)imageView;

/*
 * DestoryMediaEngine: Clear all the resource and destory the MediaEngine.
 * @ mediaEngine: MediaEngine object.
 */
+ (void)DestoryMediaEngine:(MediaEngine *)mediaEngine;
@end

/* 
 * MediaEngine Delegate:
 * Low layer messsage, or notify will be send to UI via this protocal.
 */
@protocol MediaEngineDelegate <NSObject>
  @optional
/*
 * playStarted: Media playback started notify.
 */
- (int)playStarted;
/*
 * mediaPaused: Media paused notify. 
 */
- (int)mediaPaused;
/*
 * mediaStoped: Media playback stoped notify.
 */
- (int)mediaStoped;
/*
 * seekCompleted: Seek action finished notify.
 */
- (int)seekCompleted;
/*
 * playbackFinished: Media playback finished notify.
 */
- (int)playbackFinished;
/*
 * playbackPositionUpdate: Media playback time update notify.
 * @ currPlayTime: Current playback time.
 */
- (void)playbackTimeUpdate:(unsigned int)currPlayTime;
@end
