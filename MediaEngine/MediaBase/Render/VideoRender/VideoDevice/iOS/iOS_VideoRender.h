/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * iOS_VideoRender.h
 * Here we define a class to Package the video iOS render APIs, set all these
 * APIs as a class, and this will be used in VideoRender class at iOS platform.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef IOS_VIDEO_RENDER_H
#define IOS_VIDEO_RENDER_H

#include "ECType.h"
#include "Source.h"
#include "VideoDec.h"
#include "VideoRend.h"
#include "VideoRenderDeviceI.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
};

class iOS_VideoRender : public VideoRenderDeviceI
{
public:
    iOS_VideoRender();
    ~iOS_VideoRender();
public:
    EC_U32 Init(MediaCtxInfo* pMediaInfo,
                EC_U32 nScreenWidth, 
                EC_U32 nScreenHight, 
                EC_VOIDP pDrawable);
    EC_VOID Stop();
    EC_VOID Uninit();
    EC_VOID ClearScreen();
    EC_VOID DrawFrame(VideoFrame* pFrame);
    EC_VOID UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen);
private:
    EC_U32              m_nVideoWidth;
    EC_U32              m_nVideoHeight;
    AVPicture           m_sAVPicture;
    EC_VOIDP            m_pVideoScreen;
    struct SwsContext*  m_pImgConvertCtx;
};

#undef IOS_UIKIT_INCLUDE
#endif /* IOS_VIDEO_RENDER_H */
