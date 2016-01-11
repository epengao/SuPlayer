/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ... 
* 
* Project:  Enjoyable Coding < EC >
* 
* Source.h
* This file for define the Media Source Error Code, SourceBuffer and
* MediaInfo struct.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef SOURCE_H
#define SOURCE_H

#include "ECType.h"
#include "ECError.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Media srouce Error*/
#define    Source_Err_None                   0x00000000
#define    Source_Err_Read_Video             0x00000A01
#define    Source_Err_Read_Audio             0x00000A02
#define    Source_Err_OpenFaild              0x00000F01
#define    Source_Err_NoStreamInfo           0x00000F02
#define    Source_Err_NoVideo                0x00000F03
#define    Source_Err_NoAudio                0x00000F04
#define    Source_Err_NoSubtitle             0x00000F05
#define    Source_Err_NoMediaSource          0x00000F06
#define    Source_Err_NeedRetry              0x00000F07
#define    Source_Err_ReadDataFaild          0x00000F08
#define    Source_Err_EndOfSource            0x00000F09
#define    Source_Err_NotInit                0x00000F0A

/* for whole player define */
#define    Media_Playback_EOS                0x10000001
#define    Media_AudioPlayback_EOS           0x10000002
#define    Media_VideoPlayback_EOS           0x10000003

/* SourceBuffer */
#define SourceBuffer void

/* MediaInfomation */
typedef struct
{
    EC_U32 m_nDuration;
    EC_S32 m_nAudioIndex;
    EC_S32 m_nVideoIndex;

    EC_U32 m_nVideoWidth;
    EC_U32 m_nVideoHeight;
    EC_U32 m_nFramePixFmt;
    EC_VOIDP m_pFormatInfo;
    EC_VOIDP m_pVideoCodecInfo;
    EC_VOIDP m_pAudioCodecInfo;
    EC_DOUBLE m_FrameAVGDuration;

    EC_U32 m_nChannels;
    EC_U32 m_nSampleRate;
    EC_U32 m_nSampleSize;
    EC_U32 m_nSampleFormat;
    EC_U32 m_nChannelsLayOut;
} MediaCtxInfo;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SOURCE_H */
