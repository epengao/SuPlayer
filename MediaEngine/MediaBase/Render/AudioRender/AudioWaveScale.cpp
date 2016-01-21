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
* This file for Audio Wave Scale class implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "AudioRend.h"
#include "AudioWaveScale.h"

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

AudioWaveScale::AudioWaveScale()
:m_nOutChannels(-1)
,m_pScaleOutbuffer(EC_NULL)
,m_pWaveScaleContext(EC_NULL)
,m_nOutSampleFormat(AV_SAMPLE_FMT_NONE)
{
}

AudioWaveScale::~AudioWaveScale()
{
}

EC_U32 AudioWaveScale::Init(MediaCtxInfo* pMediaInfo, AudioPCMBuffer *pFirstFrame)
{
    if (EC_NULL == pMediaInfo)
        return Audio_Render_Err_InitFail;

    EC_S32 out_sample_rate = pMediaInfo->m_nSampleRate;
    EC_S64 out_channel_layout = AV_CH_LAYOUT_STEREO;
    EC_S32 out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;

    AVCodecContext *pCodecCtx = (AVCodecContext*)(pMediaInfo->m_pAudioCodecInfo);
    EC_S64 in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);
    EC_S32 in_sample_rate = pCodecCtx->sample_rate;
    AVSampleFormat in_sample_fmt = pCodecCtx->sample_fmt;

    m_nOutChannels = out_channels;
    m_nOutSampleFormat = out_sample_fmt;

    m_pWaveScaleContext = swr_alloc();
    m_pWaveScaleContext = swr_alloc_set_opts(m_pWaveScaleContext, 
                                             out_channel_layout,
                                             out_sample_fmt,
                                             out_sample_rate,
                                             in_channel_layout, 
                                             in_sample_fmt, 
                                             in_sample_rate, 0, NULL);
    EC_S32 nRet = swr_init(m_pWaveScaleContext);
    if (nRet < 0) return Audio_Render_Err_InitFail;

    m_pScaleOutbuffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    if (m_pScaleOutbuffer == EC_NULL) return EC_Err_Memory_Low;

    return Audio_Render_Err_None;
}

EC_VOID AudioWaveScale::Uninit()
{
    av_free(m_pScaleOutbuffer);
    swr_free(&m_pWaveScaleContext);
    m_pScaleOutbuffer = EC_NULL;
}

EC_U32 AudioWaveScale::Scale(AudioPCMBuffer* pWaveIn, AudioPCMBuffer **ppWaveOut, EC_U32* pOutSize)
{
    if ((EC_NULL == pWaveIn)  ||
        (EC_NULL == ppWaveOut)||
        (EC_NULL == pOutSize))
        return EC_Err_BadParam;

    AVFrame *pAVFrameIn = (AVFrame*)(pWaveIn);
    EC_S32 out_nb_samples = pAVFrameIn->nb_samples;
    swr_convert(m_pWaveScaleContext, 
                &m_pScaleOutbuffer, MAX_AUDIO_FRAME_SIZE, 
                (const uint8_t **)pAVFrameIn->data, out_nb_samples);
    EC_U32 nOutBufSize = av_samples_get_buffer_size(NULL,
                                                    m_nOutChannels,
                                                    out_nb_samples,
                                                    m_nOutSampleFormat, 1);

    (*pOutSize) = nOutBufSize;
    (*ppWaveOut) = m_pScaleOutbuffer;

    return EC_Err_None;
}
