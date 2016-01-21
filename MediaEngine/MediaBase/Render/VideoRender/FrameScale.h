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
* Here we define Frame Scale class APIs.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef FRAME_SCLAE_H
#define FRAME_SCLAE_H

#include "ECType.h"
#include "VideoRend.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
};

class FrameScale
{
public:
    FrameScale(EC_BOOL doScale = EC_TRUE);
    ~FrameScale();
public:
    EC_U32 Init(EC_U32 nInWidth,  EC_U32 nInHight,
                EC_U32 nOutWidth, EC_U32 nOutHight, EC_U32 nFormat);
    EC_VOID Uninit();
    EC_U32 Scale(VideoFrame* pFrameIn, VideoFrame **ppFrameOut);
    EC_VOID UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen);

private:
    EC_U32             m_nInWidth;
    EC_U32             m_nInHight;
    EC_U32             m_nOutWidth;
    EC_U32             m_nOutHight;
    EC_BOOL            m_bDoScale;
    VideoFrame*        m_pFrameYUV;
    EC_U8*             m_pOutFrameBuf;
    AVPixelFormat      m_nFramePixFormat;
    struct SwsContext* m_pFrameScaleCtx;
};

#endif /* FRAME_SCLAE_H */