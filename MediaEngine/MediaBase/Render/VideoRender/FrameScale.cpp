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
* FrameScale.h
* This file for Frame Scale class implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "VideoRend.h"
#include "FrameScale.h"


FrameScale::FrameScale(EC_BOOL doScale)
:m_nInWidth(0)
,m_nInHight(0)
,m_nOutWidth(0)
,m_nOutHight(0)
,m_bDoScale(doScale)
,m_pFrameYUV(EC_NULL)
,m_pOutFrameBuf(EC_NULL)
,m_pFrameScaleCtx(EC_NULL)
{
}

FrameScale::~FrameScale()
{
}

EC_U32 FrameScale::Init(EC_U32 nInWidth, EC_U32 nInHight,
                        EC_U32 nOutWidth, EC_U32 nOutHight, EC_U32 nFormat)
{
    if (!m_bDoScale) return EC_Err_None;
    if ((0 == nInWidth) || (0 == nInHight) ||
        (0 == nOutWidth) || (0 == nOutHight))
        return Video_Render_Err_CreatFrameScaleFail;

    m_nInWidth = nInWidth;
    m_nInHight = nInHight;
    m_nOutWidth = nOutWidth;
    m_nOutHight = nOutHight;
    m_nFramePixFormat = (AVPixelFormat)nFormat;

    m_pFrameYUV = av_frame_alloc();
    if (EC_NULL == m_pFrameYUV) return EC_Err_Memory_Low;

    m_pOutFrameBuf = (EC_U8*)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, nOutWidth, nOutHight));
    if (EC_NULL == m_pOutFrameBuf)
    {
        av_free(m_pFrameYUV);
        m_pFrameYUV = EC_NULL;
        return EC_Err_Memory_Low;
    }

    avpicture_fill((AVPicture*)m_pFrameYUV, m_pOutFrameBuf, PIX_FMT_YUV420P, nOutWidth, nOutHight);
    m_pFrameScaleCtx = sws_getContext(nInWidth, nInHight, 
                                      m_nFramePixFormat,
                                      nOutWidth, nOutHight, 
                                      PIX_FMT_YUV420P, 
                                      SWS_BICUBIC, 
                                      NULL, NULL, NULL);
    if (EC_NULL == m_pFrameScaleCtx) return Video_Render_Err_CreatFrameScaleFail;

    return Video_Render_Err_None;
}

EC_VOID FrameScale::Uninit()
{
    if (!m_bDoScale) return;
    av_free(m_pOutFrameBuf);
    if (m_pFrameYUV)
    {
        AVFrame *pFrame = (AVFrame*)m_pFrameYUV;
        av_frame_free(&pFrame);
    }
	sws_freeContext(m_pFrameScaleCtx);
    m_pOutFrameBuf = EC_NULL;
    m_pFrameScaleCtx = EC_NULL;
}

EC_U32 FrameScale::Scale(VideoFrame* pFrameIn, VideoFrame **ppFrameOut)
{
    if (m_bDoScale)
    {
        if ((EC_NULL == pFrameIn) ||
            (EC_NULL == ppFrameOut))
            return EC_Err_BadParam;

        AVFrame *pAVFrameIn = (AVFrame*)(pFrameIn);
        AVFrame  *pAVFrameOut = (AVFrame*)(m_pFrameYUV);
        sws_scale(m_pFrameScaleCtx,
                 (const EC_U8* const*)pAVFrameIn->data, 
                  pAVFrameIn->linesize, 0, m_nInHight, 
                  pAVFrameOut->data, pAVFrameOut->linesize);

        (*ppFrameOut) = m_pFrameYUV;
    }
    else (*ppFrameOut) = pFrameIn;

    return EC_Err_None;
}

EC_VOID FrameScale::UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen)
{
    if (m_bDoScale)
    {
        Uninit();
        EC_U32 nOutWidth = pVideoScreen->nWidth;
        EC_U32 nOutHeight = pVideoScreen->nHeight;
        Init(m_nInWidth, m_nInHight,
             nOutWidth, nOutHeight, m_nFramePixFormat);
    }
}
