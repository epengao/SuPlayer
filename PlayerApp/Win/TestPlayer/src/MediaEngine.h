/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * MediaEngine.h
 * This file for A media player implementation low layer APIs define.
 * this part of APIs for a media player UI call.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef PLAYER_ENGINE_H
#define PLAYER_ENGINE_H

/*  Return Err Define */
#define PlayerEng_Err_None            0x00000000
#define PlayerEng_Err_InitErr         0x00000001
#define PlayerEng_Err_NotInit         0x00000002
#define PlayerEng_Err_FileNotSupport  0x00000003
#define PlayerEng_Err_VideoNotSupport 0x00000004
#define PlayerEng_Err_AudioNotSupport 0x00000005

/* Notify ID Define */
#define Notify_PlaybackFinished       0x00001000
#define Notify_SeekCompleted          0x00001001

/* PlayerEngine Handler */
typedef void* MediaEngHandle;

/* MediaEngine Play Status */
typedef enum
{
    PlayStatus_Inited = 0,
    PlayStatus_OpenMedia,
    PlayStatus_Playing,
    PlayStatus_Pause,
    PlayStatus_Stop,
    PlayStatus_UnDefine = 0xFFFF,
} PlayStatus;

/* MeidaInfo 
 * NOTE: duration use ms
 */
typedef struct
{
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned int nDuration;
    unsigned int nAudioDuration;
    unsigned int nVideoDuration;
} MediaInfo;

/* Video render drawable */
typedef struct
{
    void* pScreen;
    unsigned int nWidth;
    unsigned int nHeight;
} VideoScreen;

/* PlayerEngine notify 
 * @pUserData: User defined data, when NotifyHandler 
               callback comes take it as parameter pUserData.
 * @NotifyHandler: This is the PlayerEngine notify message to
                   user layer callback routine. ID is the notify
                   identify, pParam1 and pParam2 depends on ID.
 */
typedef struct
{
    void *pUserData;
    int (*NotifyHandler)(void *pUserData, int ID,
                         void *pParam1, void *pParam2);
} MediaNotify;

/* Export API struct */
typedef struct
{
    /*
     * Init: Do the media playerEngine init and creat a
     *       PlayerEngine handler for next APIs used as parameter.
     * @ pHandle: If init action is success, a new PlayerEngine
     *            Handler will be assgin to this out parameter.
     * @ return: If success return PlayerEng_Err_None.
     */
    int (*Init)(MediaEngHandle *pHandle);

    /*
     * OpenMedia: Open a local media file or network streaming that
     *             is specified by parameter pMediaPath.
     * @ handle: MediaEngine handle. Created by Init API.
     * @ pMediaPath: Specify a media path, local file or network streaming.
     * @ pVideoScreen: A pointer to a local drawable window for render Video.
     *                 If audio only ,can just set as NULL.
     * @ return: If success return PlayerEng_Err_None.
     */
    int (*OpenMedia)(MediaEngHandle handle, char* pMediaPath, VideoScreen *pVideoScreen);

    /*
     * Play: Play the media content which is specified by OpenMedia.
     * @ handle: MediaEngine handle. Created by Init API.
     */
    void (*Play)(MediaEngHandle handle);

    /*
     * Pause: Pause current playing.
     * @ handle: MediaEngine handle. Created by Init API.
     */
    void (*Pause)(MediaEngHandle handle);

    /*
     * Seek: Seek to a specified position of current media.
     * @ handle: MediaEngine handle. Created by Init API.
     * @ nSeekPos: Seek position of the current media content.
     */
    void (*Seek)(MediaEngHandle handle, unsigned int nSeekPos);

    /*
    * Stop: Stop current media content.
    * @ handle: MediaEngine handle. Created by Init API.
    */
    void (*Stop)(MediaEngHandle handle);

    /*
    * SetMediaNotify: Set MediaNotify to PlayerEngine, then
                      playerEngine notifies will be send to
                      user layer via NotifyHandler.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pNotify: A pointer to MediaNotify. User layer must
                 define a callback routine,maybe a userData
                 to fill this MediaNotify.
    */
    void (*SetMediaNotify)(MediaEngHandle handle, MediaNotify *pNotify);

    /*
    * GetPlayStatus: Get current media play status.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pStatus: Play status will be assgined to here.
    */
    void (*GetPlayStatus)(MediaEngHandle handle, PlayStatus *pStatus);

    /*
    * GetMediaInfo: Get the media content information.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pMediaInfo: Media information will be assgined to here.
    */
    void (*GetMediaInfo)(MediaEngHandle handle, MediaInfo *pMediaInfo);

    /*
    * GetPlayingPosition: Get current playing time position.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pPosition: Current playing time position will be assgined to here.
    * NOTE: The playing position time unit is millisecond.
    */
    void (*GetPlayingPosition)(MediaEngHandle handle, unsigned int *pPosition);

    /*
    * Reset: Clear all the resource which alloced by previous
             media content playback.
    * @ handle: MediaEngine handle. Created by Init API.
    */
    void (*Reset)(MediaEngHandle handle);

    /*
    * ResizeVideo: Set a new width and height to current video content.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pScreen: new video drawable screen with width and height.
    */
    void (*UpdateVideoScreen)(MediaEngHandle handle, VideoScreen* pScreen);

    /*
    * UnInit: Clear all the resource which alloced by media playback
    *         and destroy the PlayerEngine handle.
    * @ pHandle: pointer to the MediaEngine handle Created by Init API,
    *            after this uninit API call, it will be set as NULL.
    */
    void (*UnInit)(MediaEngHandle *pHandle);
} MediaEngineAPI;


/* PlayerEngine API entry point */
typedef void(*GetMediaEngineAPI)(MediaEngineAPI* pAPI);

#endif /* PLAYER_ENGINE_H */