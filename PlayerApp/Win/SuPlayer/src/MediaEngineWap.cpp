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
* MediaEngine.cpp
* This file for MediaEngine class imeplementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "DllLoader.h"
#include "MediaEngineWap.h"

#define VIDEO_SIZE_AGIGN 8

MediaEngine::MediaEngine(void *pDrawable,
                         unsigned int nVideoWndWidth,
                         unsigned int nVideoWndHight)
{
    m_sVideoScreen.pScreen = pDrawable;
    m_sVideoScreen.nWidth = nVideoWndWidth;
    m_sVideoScreen.nHeight = nVideoWndHight;
    VideoScreenSizeAlign();

    memset(&m_sMediaAPI, 0, sizeof(MediaEngineAPI));
    GetMediaEngineAPI(&m_sMediaAPI);
    if (m_sMediaAPI.Init) m_sMediaAPI.Init(&m_hMediaHandle);
}

MediaEngine::~MediaEngine()
{
    if (m_hMediaHandle) m_sMediaAPI.UnInit(&m_hMediaHandle);
}

int  MediaEngine::OpenMedia(char *pMediaPath)
{
    int nRet = -1;
    if (m_hMediaHandle)
    {
        nRet = m_sMediaAPI.OpenMedia(m_hMediaHandle, pMediaPath, &m_sVideoScreen);
    }
    return nRet;
}

void MediaEngine::Play()
{
    if (m_hMediaHandle) m_sMediaAPI.Play(m_hMediaHandle);
}

void MediaEngine::Pause()
{
    if (m_hMediaHandle) m_sMediaAPI.Pause(m_hMediaHandle);
}

void MediaEngine::Seek(unsigned int nPos)
{
    if (m_hMediaHandle) m_sMediaAPI.Seek(m_hMediaHandle, nPos);
}

bool MediaEngine::HasVideo()
{
    bool ret = false;
    if (m_hMediaHandle)
    {
        MediaInfo minfo;
        m_sMediaAPI.GetMediaInfo(m_hMediaHandle, &minfo);
        ret = ((minfo.nWidth != 0) && (minfo.nHeight != 0));
    }
    return ret;
}

void MediaEngine::Stop()
{
    if (m_hMediaHandle) m_sMediaAPI.Stop(m_hMediaHandle);
}

bool MediaEngine::IsPlaying()
{
    MediaEngineStatus nStatus = MediaEngineStatus_UnDefine;
    if (m_hMediaHandle)
    {
        m_sMediaAPI.GetPlayStatus(m_hMediaHandle, &nStatus);
    }
    return (nStatus == MediaEngineStatus_Playing);
}

bool MediaEngine::HasPlayMedia()
{
    MediaEngineStatus nStatus = MediaEngineStatus_UnDefine;
    if (m_hMediaHandle)
    {
        m_sMediaAPI.GetPlayStatus(m_hMediaHandle, &nStatus);
    }
    return ((nStatus == MediaEngineStatus_Pause) ||
            (nStatus == MediaEngineStatus_Playing));
}

void MediaEngine::GetMediaInfo(MediaInfo *pMediaInfo)
{
    if (m_hMediaHandle)
    {
        m_sMediaAPI.GetMediaInfo(m_hMediaHandle, pMediaInfo);
    }
}

void MediaEngine::SetMediaNotify(MediaEngineNotify *pNotify)
{
    if (m_hMediaHandle)
    {
        m_sMediaAPI.SetMediaNotify(m_hMediaHandle, pNotify);
    }
}

unsigned int MediaEngine::GetPlayPosition()
{
    unsigned int nPos = 0;
    if (m_hMediaHandle)
    {
        m_sMediaAPI.GetPlayingPosition(m_hMediaHandle, &nPos);
    }
    return nPos;
}

unsigned int MediaEngine::GetMediaDuration()
{
    unsigned int nDuration = 0;
    if (m_hMediaHandle)
    {
        MediaInfo mInfo;
        m_sMediaAPI.GetMediaInfo(m_hMediaHandle, &mInfo);
        nDuration = mInfo.nDuration;
    }
    return nDuration;
}

void MediaEngine::UpdateVideoScreen(void *pDrawable, unsigned int nVideoWidth, unsigned int nVideoHight)
{
    m_sVideoScreen.pScreen = pDrawable;
    m_sVideoScreen.nWidth = nVideoWidth;
    m_sVideoScreen.nHeight = nVideoHight;
    VideoScreenSizeAlign();

    if (m_hMediaHandle) m_sMediaAPI.UpdateVideoScreen(m_hMediaHandle, &m_sVideoScreen);
}

void MediaEngine::VideoScreenSizeAlign()
{
    unsigned int w = m_sVideoScreen.nWidth;
    unsigned int h = m_sVideoScreen.nHeight;
    m_sVideoScreen.nWidth = w + (w%VIDEO_SIZE_AGIGN);
    m_sVideoScreen.nHeight = h + (h%VIDEO_SIZE_AGIGN);
}
