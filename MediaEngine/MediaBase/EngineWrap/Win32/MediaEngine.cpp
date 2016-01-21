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
*
* This file for MediaEngine APIs implementation.
* This module is just for MediaEngine encapsulation to PlayerEngine API.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/
#include "ECDllLib.h"
#include "MediaEngine.h"
#include "MediaCommon.h"
#include "MediaEngineWrap.h"

MediaEngineNotify  g_notifyHandler;
int EngNotifyHandler(void* pUserData, int nID, 
                     void* pParam1, void* pParam2);

EC_S32 EngInit(MediaEngineHandle *pHandle)
{
    g_notifyHandler.pUserData = EC_NULL;
    g_notifyHandler.NotifyHandler = EC_NULL;
    return InitMediaEngine(pHandle);
}

EC_S32 EngOpenMedia(MediaEngineHandle handle, const char*pMediaPath, VideoScreen *pVideoScreen)
{
    return OpenMedia(handle,
                     (EC_CONST_PCHAR)pMediaPath,
                     (MediaEngVideoScreen*)pVideoScreen);
}

EC_VOID EngPlay(MediaEngineHandle handle)
{
    Play(handle);
}

EC_VOID EngPause(MediaEngineHandle handle)
{
    Pause(handle);
}

EC_VOID EngSeek(MediaEngineHandle handle, EC_U32 nSeekPos)
{
    Seek(handle, nSeekPos);
}

EC_VOID EngStop(MediaEngineHandle handle)
{
    Stop(handle);
}

EC_VOID EngSetMediaNotify(MediaEngineHandle handle, MediaEngineNotify *pNotify)
{
    if (pNotify)
    {
        g_notifyHandler.pUserData = pNotify->pUserData;
        g_notifyHandler.NotifyHandler = pNotify->NotifyHandler;
    }
    MediaEngNotify sNotify;
    sNotify.pUserData = EC_NULL;
    sNotify.NotifyHandler = EngNotifyHandler;
    SetMediaNotify(handle, &sNotify);
}

EC_VOID EngGetMediaEngineStatus(MediaEngineHandle handle, MediaEngineStatus *pStatus)
{
    GetMediaEngineStatus(handle, (MediaEngStatus*)pStatus);
}

EC_VOID EngGetMediaInfo(MediaEngineHandle handle, MediaInfo *pMediaInfo)
{
    GetMediaInfo(handle, (MediaEngMediaInfo*)pMediaInfo);
}

EC_VOID EngGetPlayingPosition(MediaEngineHandle handle, EC_U32 *pPosition)
{
    GetPlayingPosition(handle, pPosition);
}

EC_VOID EngUpdateVideoScreen(MediaEngineHandle handle, VideoScreen *pVideoScreen)
{
    UpdateVideoScreen(handle, (MediaEngVideoScreen*)pVideoScreen);
}

EC_VOID EngUnInit(MediaEngineHandle *pHandle)
{
    UnInit(pHandle);
}

int EngNotifyHandler(void* pUserData, int nID, void* pParam1, void* pParam2)
{
    int nRet = 0;
    switch (nID)
    {
    case MediaEngNotify_PlayStarted:
    {
        if (g_notifyHandler.NotifyHandler)
        {
            EC_VOIDP pUserData = g_notifyHandler.pUserData;
            MediaEngineNotifyID nID = MediaEngineNotify_PlayStarted;
            g_notifyHandler.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
        }
        break;
    }
    case MediaEngNotify_MediaPaused:
    {
        if (g_notifyHandler.NotifyHandler)
        {
            EC_VOIDP pUserData = g_notifyHandler.pUserData;
            MediaEngineNotifyID nID = MediaEngineNotify_MediaPaused;
            g_notifyHandler.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
        }
        break;
    }
    case MediaEngNotify_MediaStoped:
    {
        if (g_notifyHandler.NotifyHandler)
        {
            EC_VOIDP pUserData = g_notifyHandler.pUserData;
            MediaEngineNotifyID nID = MediaEngineNotify_MediaStoped;
            g_notifyHandler.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
        }
        break;
    }
    case MediaEngNotify_SeekCompleted:
    {
        if (g_notifyHandler.NotifyHandler)
        {
            EC_VOIDP pUserData = g_notifyHandler.pUserData;
            MediaEngineNotifyID nID = MediaEngineNotify_SeekCompleted;
            g_notifyHandler.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
        }
        break;
    }
    case MediaEngNotify_PlaybackFinished:
    {
        if (g_notifyHandler.NotifyHandler)
        {
            EC_VOIDP pUserData = g_notifyHandler.pUserData;
            MediaEngineNotifyID nID = MediaEngineNotify_PlaybackFinished;
            g_notifyHandler.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
        }
        break;
    }
    default:
        break;
    }

    return nRet;
}

VOID GetMediaEngineAPI(MediaEngineAPI* pAPI)
{
    if (pAPI != EC_NULL)
    {
        pAPI->Init = EngInit;
        pAPI->OpenMedia = EngOpenMedia;
        pAPI->Play = EngPlay;
        pAPI->Pause = EngPause;
        pAPI->Seek = EngSeek;
        pAPI->Stop = EngStop;
        pAPI->SetMediaNotify = EngSetMediaNotify;
        pAPI->GetPlayStatus = EngGetMediaEngineStatus;
        pAPI->GetMediaInfo = EngGetMediaInfo;
        pAPI->GetPlayingPosition = EngGetPlayingPosition;
        pAPI->UnInit = EngUnInit;
        pAPI->UpdateVideoScreen = EngUpdateVideoScreen;
    }
}
