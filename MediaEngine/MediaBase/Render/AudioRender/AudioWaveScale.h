/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * AudioWaveScale.h
 * Here we define Audio PCM data Scale class APIs.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef AUDIO_WAVE_SCLAE_H
#define AUDIO_WAVE_SCLAE_H

#include "ECType.h"
#include "Source.h"
#include "AudioRend.h"
extern "C"
{
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
};

class AudioWaveScale
{
public:
    AudioWaveScale();
    ~AudioWaveScale();
public:
    EC_U32 Init(MediaCtxInfo* pMediaInfo, AudioPCMBuffer *pFirstFrame);
    EC_VOID Uninit();
    EC_U32 Scale(AudioPCMBuffer* pWaveIn, AudioPCMBuffer **ppWaveOut, EC_U32* pOutSize);

private:
    EC_S32             m_nOutChannels;
    uint8_t*           m_pScaleOutbuffer;
    AVSampleFormat     m_nOutSampleFormat;
    struct SwrContext* m_pWaveScaleContext;
};

#endif /* AUDIO_WAVE_SCLAE_H */