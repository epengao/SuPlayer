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