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
* FFmpegVideoDec.h
* This file for FFmpeg video decoder APIs package to a class define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef FFMPEG_VIDEO_DEC_H
#define FFMPEG_VIDEO_DEC_H

#include "ECType.h"
#include "Source.h"
#include "VideoRend.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
};

class FFmpegVideoDec
{
public:
    FFmpegVideoDec();
    ~FFmpegVideoDec();
    EC_U32 Init(EC_VOIDP pMediaInfo);
    EC_VOID Uninit();
    EC_VOID FlushVideoFrames();
    VideoFrame* AllocVideoFrame();
    EC_VOID ReleaseVideoFrame(VideoFrame *pFrame);
    EC_VOID CopyVideoFrame(VideoFrame **ppDst, VideoFrame *pSrc);
    EC_U32 DecodeVideo(EC_VOIDP pInputData, EC_VOIDP* ppYUVFrameData);

private:
    AVFrame           *m_pFrame;
    AVCodec           *m_pCodec;
    AVCodecContext    *m_pCodecCtx;
    MediaCtxInfo      *m_pMediaInfo;
    EC_DOUBLE          m_TimeBase;
};

#endif /* FFMPEG_VIDEO_DEC_H */