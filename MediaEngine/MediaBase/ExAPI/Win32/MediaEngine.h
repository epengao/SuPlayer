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
#define MediaEngine_Err_None             0x00000000
#define MediaEngine_Err_InitErr          0x00000001
#define MediaEngine_Err_NotInit          0x00000002
#define MediaEngine_Err_FileNotSupport   0x00000003
#define MediaEngine_Err_VideoNotSupport  0x00000004
#define MediaEngine_Err_AudioNotSupport  0x00000005
#define MediaEngine_Err_UnDefine         0xFFFFFFFF

/* Notify ID Define */
typedef enum
{
    MediaEngineNotify_PlayStarted      = 1,
    MediaEngineNotify_MediaPaused      = 2,
    MediaEngineNotify_MediaStoped      = 3,
    MediaEngineNotify_SeekCompleted    = 4,
    MediaEngineNotify_PlaybackFinished = 5,
    MediaEngineNotify_UnDefine         = 0xFFFF,
} MediaEngineNotifyID;

/* MediaEngine Status */
typedef enum
{
    MediaEngineStatus_Inited     = 1,
    MediaEngineStatus_MediaOpend = 2,
    MediaEngineStatus_Playing    = 3,
    MediaEngineStatus_Seeking    = 4,
    MediaEngineStatus_Pause      = 5,
    MediaEngineStatus_Stop       = 6,
    MediaEngineStatus_Switching  = 7,
    MediaEngineStatus_UnDefine   = 0xFFFF,
} MediaEngineStatus;

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
} MediaEngineNotify;

/* MediaEngine Handler */
typedef void* MediaEngineHandle;

/* Export API struct */
typedef struct
{
    /*
     * Init: Do the media engine init and creat a
     *       MediaEngine handler for next APIs used as parameter.
     * @ pHandle: If init action is success, a new PlayerEngine
     *            Handler will be assgin to this out parameter.
     * @ return: If success return PlayerEng_Err_None.
     */
    int (*Init)(MediaEngineHandle *pHandle);

    /*
     * OpenMedia: Open a local media file or network streaming that
     *             is specified by parameter pMediaPath.
     * @ handle: MediaEngine handle. Created by Init API.
     * @ pMediaPath: Specify a media path, local file or network streaming.
     * @ pVideoScreen: A pointer to a local drawable window for render Video.
     *                 If audio only ,can just set as NULL.
     * @ return: If success return PlayerEng_Err_None.
     */
    int (*OpenMedia)(MediaEngineHandle handle, const char* pMediaPath, VideoScreen *pVideoScreen);

    /*
     * Play: Play the media content which is specified by OpenMedia.
     * @ handle: MediaEngine handle. Created by Init API.
     */
    void (*Play)(MediaEngineHandle handle);

    /*
     * Pause: Pause current playing.
     * @ handle: MediaEngine handle. Created by Init API.
     */
    void (*Pause)(MediaEngineHandle handle);

    /*
     * Seek: Seek to a specified position of current media.
     * @ handle: MediaEngine handle. Created by Init API.
     * @ nSeekPos: Seek position of the current media content.
     */
    void (*Seek)(MediaEngineHandle handle, unsigned int nSeekPos);

    /*
    * Stop: Stop current media content.
            A new media playback start after previouse,
            call this interface stop previouse one is nessesary.
    * @ handle: MediaEngine handle. Created by Init API.
    */
    void (*Stop)(MediaEngineHandle handle);

    /*
    * SetMediaNotify: Set MediaNotify to PlayerEngine, then
                      playerEngine notifies will be send to
                      user layer via NotifyHandler.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pNotify: A pointer to MediaEngineNotify. User layer must
                 define a callback routine,maybe a userData
                 to fill this MediaEngineNotify.
    */
    void (*SetMediaNotify)(MediaEngineHandle handle, MediaEngineNotify *pNotify);

    /*
    * GetPlayStatus: Get current media play status.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pStatus: Media engine status will be assgined to here.
    */
    void (*GetPlayStatus)(MediaEngineHandle handle, MediaEngineStatus *pStatus);

    /*
    * GetMediaInfo: Get the media content information.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pMediaInfo: Media information will be assgined to here.
    */
    void (*GetMediaInfo)(MediaEngineHandle handle, MediaInfo *pMediaInfo);

    /*
    * GetPlayingPosition: Get current playing time position.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pPosition: Current playing time position will be assgined to here.
    * NOTE: The playing position time unit is millisecond.
    */
    void (*GetPlayingPosition)(MediaEngineHandle handle, unsigned int *pPosition);

    /*
    * UpdateVideoScreen: Set a new width and height or drwable of video.
    * @ handle: MediaEngine handle. Created by Init API.
    * @ pScreen: new video drawable screen with width and height.
    */
    void (*UpdateVideoScreen)(MediaEngineHandle handle, VideoScreen* pScreen);

    /*
    * UnInit: Clear all the resource which alloced by media playback
    *         and destroy the PlayerEngine handle.
    * @ pHandle: pointer to the MediaEngine handle Created by Init API,
    *            after this uninit API call, it will be set as NULL.
    */
    void (*UnInit)(MediaEngineHandle *pHandle);
} MediaEngineAPI;

/* ExpAIP*/
#ifdef __cplusplus
#define MediaEngineExAPI extern "C" __declspec (dllexport)
#else
#define MediaEngineExAPI            __declspec (dllexport)
#endif

/* MediaEngine API entry point */
MediaEngineExAPI void GetMediaEngineAPI(MediaEngineAPI* pAPI);

#endif /* PLAYER_ENGINE_H */
