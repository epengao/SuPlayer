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
* SDL_VideoRender.h
* Here we define a class to Package the video SDL render APIs, set all these
* APIs as a class, and this will be used in VideoRender class.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef SDL_VIDEO_RENDER_H
#define SDL_VIDEO_RENDER_H

#include "ECType.h"
#include "Source.h"
#include "VideoDec.h"
#include "VideoRend.h"
#include "MediaCommon.h"
#include "VideoRenderDeviceI.h"

extern "C"
{
#include "sdl/SDL.h"
#include "libavcodec/avcodec.h"
};

class SDL_VideoRender : public VideoRenderDeviceI
{
public:
    SDL_VideoRender();
    ~SDL_VideoRender();
public:
    EC_U32 Init(MediaCtxInfo* pMediaInfo,
                EC_U32 nScreenWidth, 
                EC_U32 nScreenHight, 
                EC_VOIDP pDrawable);
    EC_VOID Uninit();
    EC_VOID ClearScreen();
    EC_VOID DrawFrame(VideoFrame* pFrame);
    EC_VOID UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen);

private:
    EC_VOID EraseVideoRim();
    EC_VOID SetVideoRect(SDL_Rect *pRect);
private:
    EC_VOIDP     m_pDrawable;
    SDL_Rect     m_sSDLRect;
    SDL_Surface* m_pScreen;
    SDL_Overlay* m_pOverlay;
    EC_U32       m_nVideoWidth;
    EC_U32       m_nVideoHeight;
    EC_U32       m_nWindowWidth;
    EC_U32       m_nWindowHeight;
    EC_U32       m_nScreenWidth;
    EC_U32       m_nScreenHeight;
};

#endif /* SDL_VIDEO_RENDER_H */