/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* FFmpegReader.cpp
* This file for Media FFmpeg Source data reader Class Implemetaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECLog.h"
#include "FFmpegReader.h"

FFmpegReader::FFmpegReader(EC_CONST_PCHAR pMediaPath)
:m_nVideoIndex(-1)
,m_nAudioIndex(-1)
,m_pFormatCtx(EC_NULL)
,m_strMediaPath(pMediaPath)
{
}

FFmpegReader::~FFmpegReader()
{
}

EC_U32 FFmpegReader::Init()
{
    av_register_all();
    avformat_network_init();
    m_pFormatCtx = avformat_alloc_context();
    if (avformat_open_input(&m_pFormatCtx, m_strMediaPath.ToCStr(), NULL, NULL)!=0)
    {
        return Source_Err_OpenFaild;
    }
    if (avformat_find_stream_info(m_pFormatCtx,NULL)<0)
    {
        return Source_Err_NoStreamInfo;
    }
    if (m_nVideoIndex == -1)
    {
        for (EC_S32 i = 0; i < m_pFormatCtx->nb_streams; i++)
        {
            if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_nVideoIndex = i;
                break;
            }
        }
        if (m_nVideoIndex == -1)
        {
            secLogE("Can not find video stream.");
        }
    }
    if (m_nAudioIndex == -1)
    {
        for (EC_S32 i = 0; i < m_pFormatCtx->nb_streams; i++)
        {
            if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                m_nAudioIndex = i;
                break;
            }
        }
        if (m_nAudioIndex == -1)
        {
            secLogE("Can not find video stream.");
        }
    }

    if ((m_nAudioIndex == -1) && (m_nVideoIndex == -1))
        return Source_Err_NoMediaSource;

    return Source_Err_None;
}

EC_U32 FFmpegReader::Seek(EC_U32 nPos)
{
    avformat_flush(m_pFormatCtx);
    int64_t timestamp = (int64_t)nPos * 1000;
    int nRet = av_seek_frame(m_pFormatCtx,-1, timestamp, AVSEEK_FLAG_BACKWARD);
    if (nRet < 0) return EC_Err_OperatorFaild;

    return EC_Err_None;
}

EC_U32 FFmpegReader::ReadSourceBuffer(SourceBuffer** ppBuffer)
{
    EC_U32 nRet = Source_Err_None;
    if (ppBuffer)
    {
        if (EC_NULL == (*ppBuffer))
        {
            AVPacket *pPkg = (AVPacket *)av_malloc(sizeof(AVPacket));
            av_init_packet(pPkg);
            (*ppBuffer) = pPkg;
        }
        AVPacket *pPacket = (AVPacket*)(*ppBuffer);
        if (EC_NULL == pPacket) return EC_Err_Memory_Low;

        EC_S32 nReadRet = av_read_frame(m_pFormatCtx, pPacket);
        if (nReadRet >= 0)
        {
            if (pPacket->stream_index == m_nVideoIndex)
            {
                return Source_Err_Read_Video;
            }
            else if (pPacket->stream_index == m_nAudioIndex)
            {
                return Source_Err_Read_Audio;
            }
            else nRet = Source_Err_NeedRetry;
        }
        else if (AVERROR_EOF == nReadRet)
            nRet = Source_Err_EndOfSource;
        else
            nRet = Source_Err_ReadDataFaild;
    }
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

EC_VOID FFmpegReader::ReleaseSourceBuffer(EC_VOIDP pBuffer)
{
    av_free_packet((AVPacket*)pBuffer);
}

EC_VOID FFmpegReader::Uninit()
{
    avformat_close_input(&m_pFormatCtx);
}

EC_U32 FFmpegReader::GetMediaInfo(MediaCtxInfo **ppMediaInfo)
{
    if (EC_NULL == ppMediaInfo)
        return EC_Err_BadParam;
    if (EC_NULL == m_pFormatCtx)
        return Source_Err_NotInit;

    (*ppMediaInfo)->m_nVideoWidth = 0;
    (*ppMediaInfo)->m_nVideoHeight = 0;
    (*ppMediaInfo)->m_nAudioIndex = m_nAudioIndex;
    (*ppMediaInfo)->m_nVideoIndex = m_nVideoIndex;
    (*ppMediaInfo)->m_pFormatInfo = m_pFormatCtx;
    (*ppMediaInfo)->m_nDuration = (EC_U32)(m_pFormatCtx->duration / 1000);
    if (m_nAudioIndex != -1)
    {
        AVCodecContext *pACodecCtx = m_pFormatCtx->streams[m_nAudioIndex]->codec;
        (*ppMediaInfo)->m_pAudioCodecInfo = m_pFormatCtx->streams[m_nAudioIndex]->codec;
        (*ppMediaInfo)->m_nChannels = pACodecCtx->channels;
        (*ppMediaInfo)->m_nSampleRate = pACodecCtx->sample_rate;
        (*ppMediaInfo)->m_nSampleSize = pACodecCtx->frame_size;
        (*ppMediaInfo)->m_nSampleFormat = pACodecCtx->sample_fmt;
        (*ppMediaInfo)->m_nChannelsLayOut = (EC_U32)pACodecCtx->channel_layout;
    }
    if (m_nVideoIndex != -1)
    {
        AVStream *pVideoStream = m_pFormatCtx->streams[m_nVideoIndex];
        AVCodecContext *pVCodecCtx = m_pFormatCtx->streams[m_nVideoIndex]->codec;
        EC_DOUBLE dFps = 0;
        EC_S32 fps = pVideoStream->avg_frame_rate.den && pVideoStream->avg_frame_rate.num;
        EC_S32 tbr = pVideoStream->r_frame_rate.den && pVideoStream->r_frame_rate.num;
        EC_S32 tbn = pVideoStream->time_base.den && pVideoStream->time_base.num;
        EC_S32 tbc = pVideoStream->codec->time_base.den && pVideoStream->codec->time_base.num;
        if (fps)
            dFps = av_q2d(av_make_q(pVideoStream->avg_frame_rate.den,
            pVideoStream->avg_frame_rate.num));
        else if (tbr)
            dFps = av_q2d(av_make_q(pVideoStream->r_frame_rate.den,
            pVideoStream->r_frame_rate.num));
        else if (tbn)
            dFps = av_q2d(pVideoStream->time_base);
        else if (tbc)
            dFps = av_q2d(pVideoStream->codec->time_base);
        (*ppMediaInfo)->m_nVideoWidth = pVCodecCtx->width;
        (*ppMediaInfo)->m_nVideoHeight = pVCodecCtx->height;
        (*ppMediaInfo)->m_nFramePixFmt = pVCodecCtx->pix_fmt;
        (*ppMediaInfo)->m_pVideoCodecInfo = m_pFormatCtx->streams[m_nVideoIndex]->codec;
        (*ppMediaInfo)->m_FrameAVGDuration = dFps;
    }

    return EC_Err_None;
}
