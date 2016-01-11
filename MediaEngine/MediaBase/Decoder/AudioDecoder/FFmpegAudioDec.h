/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * FFmpegAudioDec.h
 * This file for FFmpeg Audio decoder APIs package to a class define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef FFMPEG_AUDIO_DEC_H
#define FFMPEG_AUDIO_DEC_H

#include "ECType.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
};

class FFmpegAudioDec
{
public:
    FFmpegAudioDec();
    ~FFmpegAudioDec();
    EC_U32 Init(EC_VOIDP pMediaInfo);
    EC_VOID Uninit();
    EC_VOID FlushAuidoPCMBufs();
    AudioPCMBuffer* AllocAudioPCMBuffer();
    EC_VOID ReleaseAudioPCMBuffer(AudioPCMBuffer *pBuffer);
    EC_VOID CopyAudioPCMBuffer(AudioPCMBuffer **ppDst, AudioPCMBuffer *pSrc);
    EC_U32 DecodeAudio(EC_VOIDP pInputData, EC_VOIDP* ppAudioPCMBuffer);

private:
    AVFrame           *m_pPCM;
    AVCodec           *m_pCodec;
    AVCodecContext    *m_pCodecCtx;
    EC_DOUBLE          m_TimeBase;
};

#endif /* FFMPEG_AUDIO_DEC_H */