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
* SDL_VideoRender.cpp
* This file is SDL_VideoRender class implementation
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include <Windows.h>
#include "Source.h"
#include "VideoRend.h"
#include "SDL_VideoRender.h"


SDL_VideoRender::SDL_VideoRender()
:m_pDrawable(EC_NULL)
,m_pScreen(EC_NULL)
,m_pOverlay(EC_NULL)
,m_nVideoWidth(0)
,m_nVideoHeight(0)
,m_nWindowWidth(0)
,m_nWindowHeight(0)
,m_nScreenWidth(0)
,m_nScreenHeight(0)
{
}

SDL_VideoRender::~SDL_VideoRender()
{
}

EC_U32 SDL_VideoRender::Init(MediaCtxInfo* pMediaInfo,
                             EC_U32 nScreenWidth, 
                             EC_U32 nScreenHight, 
                             EC_VOIDP pDrawable)
{
    if (EC_NULL == pMediaInfo)
        return EC_Err_BadParam;

    AVCodecContext *pCodecCtx = (AVCodecContext*)(pMediaInfo->m_pVideoCodecInfo);
    if ((0 == nScreenWidth) || (0 == nScreenHight))
    {
        nScreenWidth = pCodecCtx->width;
        nScreenHight = pCodecCtx->height;
    }

    m_pDrawable = pDrawable;
    char pEnvStr[256] = { 0 };
    sprintf_s(pEnvStr, 255, "SDL_WINDOWID=0x%lx", pDrawable);
    SDL_putenv(pEnvStr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return Video_Render_Err_InitFail;

    m_nWindowWidth = nScreenWidth;
    m_nWindowHeight = nScreenHight;
    m_nVideoWidth = pCodecCtx->width;
    m_nVideoHeight = pCodecCtx->height;

    m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    EC_U32 nFlag = 0;
    if (m_pDrawable == EC_NULL)
        nFlag = SDL_FULLSCREEN;
    m_pScreen = SDL_SetVideoMode(m_nScreenWidth, m_nScreenHeight, 0, nFlag);
    if (EC_NULL == m_pScreen)
        return Video_Render_Err_CreatWindowFail;
    m_pOverlay = SDL_CreateYUVOverlay(m_nWindowWidth, m_nWindowHeight, SDL_YV12_OVERLAY, m_pScreen);
    if (EC_NULL == m_pOverlay)
        return Video_Render_Err_CreatRenderFail;
    SetVideoRect(&m_sSDLRect);

    return Video_Render_Err_None;
}

EC_VOID SDL_VideoRender::Uninit()
{
    SDL_FreeSurface(m_pScreen);
    SDL_FreeYUVOverlay(m_pOverlay);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

EC_VOID SDL_VideoRender::ClearScreen()
{
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = m_nScreenWidth;
    clipRect.h = m_nScreenHeight;
    SDL_FillRect(m_pScreen, &clipRect, 0x0);
}

EC_VOID SDL_VideoRender::DrawFrame(VideoFrame* pFrame)
{
    if (EC_NULL == pFrame) return;

    AVFrame *pFrameYUV = (AVFrame*)pFrame;
    m_pOverlay->pixels[0] = pFrameYUV->data[0];
    m_pOverlay->pixels[2] = pFrameYUV->data[1];
    m_pOverlay->pixels[1] = pFrameYUV->data[2];
    m_pOverlay->pitches[0] = pFrameYUV->linesize[0];
    m_pOverlay->pitches[2] = pFrameYUV->linesize[1];
    m_pOverlay->pitches[1] = pFrameYUV->linesize[2];

    SDL_DisplayYUVOverlay(m_pOverlay, &m_sSDLRect);
}

EC_VOID SDL_VideoRender::UpdateVideoScreen(MediaEngVideoScreen *pVideoScreen)
{
    m_nWindowWidth = pVideoScreen->nWidth;
    m_nWindowHeight = pVideoScreen->nHeight;
    EC_VOIDP pDrawable = pVideoScreen->pScreen;

    if (pDrawable != m_pDrawable)
    {
        EC_U32 nFlag = 0;
        SDL_FreeSurface(m_pScreen);
        if (m_pDrawable == EC_NULL) nFlag = SDL_FULLSCREEN;
        m_pScreen = SDL_SetVideoMode(m_nScreenWidth, m_nScreenHeight, 0, nFlag);
    }
    SDL_FreeYUVOverlay(m_pOverlay);
    m_pOverlay = SDL_CreateYUVOverlay(m_nWindowWidth, m_nWindowHeight, SDL_YV12_OVERLAY, m_pScreen);

    SetVideoRect(&m_sSDLRect);
    EraseVideoRim();
}

/* Private Method */
EC_VOID SDL_VideoRender::SetVideoRect(SDL_Rect *pRect)
{
    if (pRect == EC_NULL) return;

    EC_U32 nTmpWidth = m_nWindowWidth;
    EC_U32 nTmpHeight = m_nVideoHeight * nTmpWidth / m_nVideoWidth;
    pRect->x = 0;
    pRect->y = (m_nWindowHeight - nTmpHeight) / 2;

    if (nTmpHeight > m_nWindowHeight)
    {
        nTmpHeight = m_nWindowHeight;
        nTmpWidth = m_nVideoWidth * nTmpHeight / m_nVideoHeight;
        pRect->y = 0;
        pRect->x = (m_nWindowWidth - nTmpWidth) / 2;
    }

    pRect->w = nTmpWidth;
    pRect->h = nTmpHeight;
}

EC_VOID SDL_VideoRender::EraseVideoRim()
{
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    if (m_sSDLRect.w == m_nWindowWidth)
    {
        clipRect.w = m_sSDLRect.w;
        clipRect.h = m_sSDLRect.y;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
        clipRect.y = m_nWindowHeight - m_sSDLRect.y;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
    }
    else
    {
        clipRect.w = m_sSDLRect.x;
        clipRect.h = m_sSDLRect.h;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
        clipRect.x = m_nWindowWidth - m_sSDLRect.x;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
    }

    if (m_nScreenWidth > m_nWindowWidth)
    {
        clipRect.y = 0;
        clipRect.x = m_nWindowWidth;
        clipRect.w = m_nScreenWidth - m_nWindowWidth;
        clipRect.h = m_nWindowHeight;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
    }
    if (m_nVideoHeight > m_nWindowHeight)
    {
        clipRect.x = 0;
        clipRect.y = m_nWindowHeight;
        clipRect.w = m_nWindowWidth;
        clipRect.h = m_nVideoHeight - m_nWindowHeight;
        SDL_FillRect(m_pScreen, &clipRect, 0x0);
    }
}
