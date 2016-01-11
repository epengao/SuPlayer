/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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