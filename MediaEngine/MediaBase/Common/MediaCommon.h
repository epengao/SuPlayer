/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * MediaCommon.h
 * This file for defining all the media common info, such as media
 * command, media status, media communication message.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef MEDIA_COMMON_H
#define MEDIA_COMMON_H

#include "ECType.h"


typedef void* MediaEngHandle;

typedef enum
{
    MediaEng_Err_None             = 0x00000000,
    MediaEng_Err_InitErr          = 0x00000001,
    MediaEng_Err_NotInit          = 0x00000002,
    MediaEng_Err_FileNotSupport   = 0x00000003,
    MediaEng_Err_VideoNotSupport  = 0x00000004,
    MediaEng_Err_AudioNotSupport  = 0x00000005,
    MediaEng_Err_UnDefine         = EC_U32_MAX,
} MediaEngErrCode;

typedef enum
{
    MediaEngStatus_Inited     = 1,
    MediaEngStatus_MediaOpend = 2,
    MediaEngStatus_Playing    = 3,
    MediaEngStatus_Seeking    = 4,
    MediaEngStatus_Pause      = 5,
    MediaEngStatus_Stop       = 6,
    MediaEngStatus_Switching  = 7,
    MediaEngStatus_UnDefine   = EC_U16_MAX,
} MediaEngStatus;

typedef enum
{
    MediaEngNotify_PlayStarted      = 0x00000001,
    MediaEngNotify_MediaPaused      = 0x00000002,
    MediaEngNotify_MediaStoped      = 0x00000003,
    MediaEngNotify_SeekCompleted    = 0x00000004,
    MediaEngNotify_PlaybackFinished = 0x00000005,
    
    /* MediaEng Flush completed */
    MediaEngNotify_FlushCompleted     = 0x00100111,
    MediaEngNotify_SrcFlushCompleted  = 0x00100001,
    MediaEngNotify_ADecFlushCompleted = 0x00100010,
    MediaEngNotify_VDecFlushCompleted = 0x00100100,
    MediaEngNotify_ARndFlushCompleted = 0x00101000,
    MediaEngNotify_VRndFlushCompleted = 0x00110000,
    /* MediaEng stopd notify */
    MediaEngNotify_EngStoped          = 0x00211111,
    MediaEngNotify_EngSrcStoped       = 0x00200001,
    MediaEngNotify_EngADecStoped      = 0x00200010,
    MediaEngNotify_EngVDecStoped      = 0x00200100,
    MediaEngNotify_EngARndStoped      = 0x00201000,
    MediaEngNotify_EngVRndStoped      = 0x00210000,
    /* MediaEng playback finished notify */
    MediaEngNotify_EngPlayFinished     = 0x00300011,
    MediaEngNotify_EngARndPlayFinished = 0x00300001,
    MediaEngNotify_EngVRndPlayFinished = 0x00300010,

    MediaEngNotify_UnDefine          = EC_U32_MAX,
} MediaEngNotifyID;

typedef enum
{
    MediaEngCommand_Play      = 0,
    MediaEngCommand_Pause     = 1,
    MediaEngCommand_Seek      = 2,
    MediaEngCommand_Stop      = 3,
    MediaEngCommand_Flush     = 4,
    MediaEngCommand_UnDefine  = EC_U16_MAX,
} MediaEngCommand;

typedef struct
{
    void* pScreen;
    unsigned int nWidth;
    unsigned int nHeight;
} MediaEngVideoScreen;

typedef struct
{
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned int nDuration;
    unsigned int nAudioDuration;
    unsigned int nVideoDuration;
} MediaEngMediaInfo;

typedef struct
{
    EC_U32 nID;
    EC_VOIDP pParam;
    MediaEngCommand nCmd;
} MediaEngMsg;

typedef struct
{
    EC_VOIDP pUserData;
    EC_S32(*NotifyHandler)(EC_VOIDP pUserData, EC_S32 ID,
                           EC_VOIDP pParam1, EC_VOIDP pParam2);
} MediaEngNotify;

#endif /* MEDIA_COMMON_H */
