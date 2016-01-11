/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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