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

#include "Framework.h"
#include "MediaCommon.h"
#include "MediaEngineWrap.h"


EC_S32 InitMediaEngine(MediaEngHandle *pHandle)
{
    *pHandle = new Framework();
    return MediaEng_Err_None;
}

EC_S32 OpenMedia(MediaEngHandle handle, EC_CONST_PCHAR pMediaPath, MediaEngVideoScreen *pVideoScreen)
{
    EC_S32 nRet = MediaEng_Err_None;
    if (handle == EC_NULL)
        nRet = MediaEng_Err_NotInit;
    else
    {
        Framework* pFramework = (Framework*)handle;
        nRet = pFramework->OpenMedia(pMediaPath, pVideoScreen);
    }
    return nRet;
}

EC_VOID Play(MediaEngHandle handle)
{
    if (handle != EC_NULL)
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->Play();
    }
}

EC_VOID Pause(MediaEngHandle handle)
{
    if (handle != EC_NULL)
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->Pause();
    }
}

EC_VOID Seek(MediaEngHandle handle, EC_U32 nSeekPos)
{
    if (handle != EC_NULL)
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->Seek(nSeekPos);
    }
}

EC_VOID Stop(MediaEngHandle handle)
{
    if (handle != EC_NULL)
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->Stop();
    }
}

EC_VOID SetMediaNotify(MediaEngHandle handle, MediaEngNotify *pNotify)
{
    if ((handle != EC_NULL) && (pNotify != EC_NULL))
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->SetMediaNotify(pNotify);
    }
}

EC_VOID GetMediaEngineStatus(MediaEngHandle handle, MediaEngStatus *pStatus)
{
    if ((handle != EC_NULL) && (pStatus != EC_NULL))
    {
        Framework* pFramework = (Framework*)handle;
        (*pStatus) = (MediaEngStatus)pFramework->GetPlayStatus();
    }
}

EC_VOID GetMediaInfo(MediaEngHandle handle, MediaEngMediaInfo *pMediaInfo)
{
    if ((handle != EC_NULL) && (pMediaInfo != EC_NULL))
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->GetMediaInfo(pMediaInfo);
    }
}

EC_VOID GetPlayingPosition(MediaEngHandle handle, EC_U32 *pPosition)
{
    if ((handle != EC_NULL) && (pPosition != EC_NULL))
    {
        Framework* pFramework = (Framework*)handle;
        (*pPosition) = pFramework->GetPlayingPosition();
    }
}

EC_VOID UpdateVideoScreen(MediaEngHandle handle, MediaEngVideoScreen *pVideoScreen)
{
    if (handle != EC_NULL)
    {
        Framework* pFramework = (Framework*)handle;
        pFramework->UpdateVideoScreen(pVideoScreen);
    }
}

EC_VOID UnInit(MediaEngHandle *pHandle)
{
    if (pHandle != EC_NULL)
    {
        Framework* pFramework = (Framework*)(*pHandle);
        delete pFramework;
        *pHandle = EC_NULL;
    }
}
