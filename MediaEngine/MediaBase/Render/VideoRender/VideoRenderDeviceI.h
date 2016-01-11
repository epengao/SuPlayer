/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoRenderDeviceI.h
 *
 * Here we define a Interface for defferent Platform following.
 * Different platform need implement individual video render device.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_RENDER_DEVICE_I_H
#define VIDEO_RENDER_DEVICE_I_H

#include "ECType.h"
#include "Source.h"
#include "VideoRend.h"

class VideoRenderDeviceI
{
public:
    virtual ~VideoRenderDeviceI(){};
    virtual EC_U32 Init(
                        MediaCtxInfo* pMediaInfo,
                        EC_U32 nScreenWidth,
                        EC_U32 nScreenHight,
                        EC_VOIDP pDrawable) = 0;
    virtual EC_VOID Uninit() = 0;
    virtual EC_VOID Stop() {};
    virtual EC_VOID ClearScreen() = 0;
    virtual EC_VOID DrawFrame(VideoFrame* pFrame) = 0;
    virtual EC_VOID UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen) = 0;
};

#endif /* VIDEO_RENDER_DEVICE_I_H */
