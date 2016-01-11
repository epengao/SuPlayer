/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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