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
