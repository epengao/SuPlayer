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