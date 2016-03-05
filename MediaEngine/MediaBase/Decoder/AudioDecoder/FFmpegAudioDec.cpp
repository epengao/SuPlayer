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
* FFmpegAudioDec.cpp
* This file for FFmpeg audio decoder APIs package to a class implementaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "Source.h"
#include "ECError.h"
#include "AudioDec.h"
#include "MediaClock.h"
#include "FFmpegAudioDec.h"


FFmpegAudioDec::FFmpegAudioDec()
:m_pPCM(EC_NULL)
,m_pCodec(EC_NULL)
,m_pCodecCtx(EC_NULL)
,m_TimeBase(0)
{
}

FFmpegAudioDec::~FFmpegAudioDec()
{
}

EC_U32 FFmpegAudioDec::Init(EC_VOIDP pMediaInfo)
{
    if (EC_NULL == pMediaInfo)
        return EC_Err_BadParam;

    MediaCtxInfo *pMediaInfoIn = (MediaCtxInfo*)pMediaInfo;
    m_pCodecCtx = (AVCodecContext*)(pMediaInfoIn->m_pAudioCodecInfo);
    m_pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);

    AVFormatContext  *pFormatCtx = (AVFormatContext*)(pMediaInfoIn->m_pFormatInfo);
    AVStream *pAudioStream = pFormatCtx->streams[pMediaInfoIn->m_nAudioIndex];
    m_TimeBase = av_q2d(pAudioStream->time_base);

    if (EC_NULL == m_pCodec)
    {
        return Audio_Dec_Err_NoDecoder;
    }
    if (avcodec_open2(m_pCodecCtx, m_pCodec, EC_NULL) < 0)
    {
        return Audio_Dec_Err_OpenDecoderFaild;
    }
    m_pPCM = av_frame_alloc();
    if (EC_NULL == m_pPCM)
    {
        return EC_Err_Memory_Low;
    }

    return Audio_Dec_Err_None;
}

EC_VOID FFmpegAudioDec::Uninit()
{
    //av_free(m_pFrame);
    avcodec_close(m_pCodecCtx);
    m_pCodecCtx = EC_NULL;
}

EC_VOID FFmpegAudioDec::FlushAuidoPCMBufs()
{
    avcodec_flush_buffers(m_pCodecCtx);
}

AudioPCMBuffer* FFmpegAudioDec::AllocAudioPCMBuffer()
{
    AVFrame *pFrame = av_frame_alloc();
    return (AudioPCMBuffer*)pFrame;
}

EC_VOID FFmpegAudioDec::ReleaseAudioPCMBuffer(AudioPCMBuffer *pFrame)
{
    if (pFrame)
    {
        AVFrame* pAVFrame = (AVFrame*)pFrame;
        av_frame_free(&pAVFrame);
    }
}

EC_VOID FFmpegAudioDec::CopyAudioPCMBuffer(AudioPCMBuffer **ppDst, AudioPCMBuffer *pSrc)
{
    AVFrame *pSrcFrame = (AVFrame*)pSrc;
    AVFrame *pDstFrame = *(AVFrame**)ppDst;

    if ((pDstFrame->channels != pSrcFrame->channels) ||
        (pDstFrame->nb_samples != pSrcFrame->nb_samples) ||
        (pDstFrame->channel_layout != pSrcFrame->channel_layout))
    {
        av_frame_free((AVFrame**)ppDst);
        (*ppDst) = av_frame_clone(pSrcFrame);
        return;
    }

    pDstFrame->format = pSrcFrame->format;
    pDstFrame->channels = pSrcFrame->channels;
    pDstFrame->channel_layout = pSrcFrame->channel_layout;
    pDstFrame->nb_samples = pSrcFrame->nb_samples;
    pDstFrame->pts = pSrcFrame->pts;
    pDstFrame->pkt_dts = pSrcFrame->pkt_dts;
    pDstFrame->pkt_pts = pSrcFrame->pkt_pts;

    av_frame_copy(pDstFrame, pSrcFrame);
}

EC_U32 FFmpegAudioDec::DecodeAudio(EC_VOIDP pInputData, EC_VOIDP* ppAudioPCMBuffer)
{
    EC_U32 nRet;
    EC_S32 decRet;
    EC_S32 decPCMOK = 0;
    AVPacket* pAudioData = (AVPacket*)pInputData;

    decRet = avcodec_decode_audio4(m_pCodecCtx, m_pPCM, &decPCMOK, pAudioData);
    if (decRet < 0) nRet = Audio_Dec_Err_DecDataFaild;
    else if (decPCMOK)
    {
        if (m_pPCM->channel_layout == 0)
            m_pPCM->channel_layout = av_get_default_channel_layout(m_pCodecCtx->channels);
        TimeStamp pts = 0;
        if (m_pPCM->pts != AV_NOPTS_VALUE)
            pts = m_pPCM->pts;
        else if (pAudioData->pts != AV_NOPTS_VALUE)
            pts = pAudioData->pts;
        m_pPCM->pts = m_TimeBase * pts * TIME_UNIT;

        *ppAudioPCMBuffer = m_pPCM;
        if (decRet < pAudioData->size)
            nRet = Audio_Dec_Err_Continue;
        else
            nRet = Audio_Dec_Err_None;
        //printf("DecoAudioTime = %d\n", m_pPCM->pts);
    }
    else nRet = Audio_Dec_Err_NeedRetry;

    return nRet;
}

