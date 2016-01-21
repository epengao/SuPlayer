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
* FFmpegVideoDec.cpp
* This file for FFmpeg video decoder APIs package to a class implementaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECError.h"
#include "VideoDec.h"
#include "MediaClock.h"
#include "FFmpegVideoDec.h"


FFmpegVideoDec::FFmpegVideoDec()
:m_pFrame(EC_NULL)
,m_pCodec(EC_NULL)
,m_pCodecCtx(EC_NULL)
,m_pMediaInfo(EC_NULL)
,m_TimeBase(0)
{
}

FFmpegVideoDec::~FFmpegVideoDec()
{
}

EC_U32 FFmpegVideoDec::Init(EC_VOIDP pMediaInfo)
{
    if (EC_NULL == pMediaInfo)
        return EC_Err_BadParam;

    m_pMediaInfo = (MediaCtxInfo*)pMediaInfo;
    m_pCodecCtx = (AVCodecContext*)(m_pMediaInfo->m_pVideoCodecInfo);
    m_pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);

    AVFormatContext  *pFormatCtx = (AVFormatContext*)(m_pMediaInfo->m_pFormatInfo);
    AVStream *pVideoStream = pFormatCtx->streams[m_pMediaInfo->m_nVideoIndex];
    m_TimeBase = av_q2d(pVideoStream->time_base);

    if (EC_NULL == m_pCodec)
    {
        return Video_Dec_Err_NoDecoder;
    }
    if (avcodec_open2(m_pCodecCtx, m_pCodec, EC_NULL) < 0)
    {
        return Video_Dec_Err_OpenDecoderFaild;
    }
    m_pFrame = av_frame_alloc();
    if (EC_NULL == m_pFrame)
    {
        return EC_Err_Memory_Low;
    }

    return Video_Dec_Err_None;
}

EC_VOID FFmpegVideoDec::Uninit()
{
    //av_free(m_pFrame);
    avcodec_close(m_pCodecCtx);
    m_pCodecCtx = EC_NULL;
}

EC_VOID FFmpegVideoDec::FlushVideoFrames()
{
    avcodec_flush_buffers(m_pCodecCtx);
}

VideoFrame* FFmpegVideoDec::AllocVideoFrame()
{
    AVFrame *pFrame = av_frame_alloc();
    return (VideoFrame*)pFrame;
}

EC_VOID FFmpegVideoDec::ReleaseVideoFrame(VideoFrame *pFrame)
{
    if (pFrame)
    {
        AVFrame* pAVFrame = (AVFrame*)pFrame;
        av_frame_free(&pAVFrame);
    }
}

EC_VOID FFmpegVideoDec::CopyVideoFrame(VideoFrame **ppDst, VideoFrame *pSrc)
{
    AVFrame *pSrcFrame = (AVFrame*)pSrc;
    AVFrame *pDstFrame = *(AVFrame**)ppDst;

    if( (pDstFrame->width != pSrcFrame->width) ||
        (pDstFrame->height != pSrcFrame->height) )
    {
        av_frame_free((AVFrame**)ppDst);
        (*ppDst) = av_frame_clone(pSrcFrame);
        return;
    }

    pDstFrame->format = pSrcFrame->format;
    pDstFrame->width = pSrcFrame->width;
    pDstFrame->height = pSrcFrame->height;
    pDstFrame->pts = pSrcFrame->pts;
    pDstFrame->pkt_dts = pSrcFrame->pkt_dts;
    pDstFrame->pkt_pts = pSrcFrame->pkt_pts;
    pDstFrame->key_frame = pSrcFrame->key_frame;
    pDstFrame->pict_type = pSrcFrame->pict_type;

    av_frame_copy(pDstFrame, pSrcFrame);
}

EC_U32 FFmpegVideoDec::DecodeVideo(EC_VOIDP pInputData, EC_VOIDP* ppYUVFrameData)
{
    EC_U32 nRet;
    EC_S32 decRet;
    EC_S32 decFrameOK = 0;
    AVPacket* pVideoData = (AVPacket*)pInputData;

    decRet = avcodec_decode_video2(m_pCodecCtx, m_pFrame, &decFrameOK, pVideoData);
    if (decRet < 0) nRet = Video_Dec_Err_DecDataFaild;
    else if (decFrameOK)
    {
        TimeStamp pts = 0;
        if (m_pFrame->pts != AV_NOPTS_VALUE)
            pts = m_pFrame->pts;
        else if (m_pFrame->pkt_pts != AV_NOPTS_VALUE)
            pts = m_pFrame->pkt_pts;
        else if (m_pFrame->pkt_dts != AV_NOPTS_VALUE)
            pts = m_pFrame->pkt_dts;
        m_pFrame->pts = m_TimeBase * pts * TIME_UNIT;

        (*ppYUVFrameData) = m_pFrame;
        nRet = Video_Dec_Err_None;
    }
    else
        nRet = Video_Dec_Err_NeedRetry;

    return nRet;
}
