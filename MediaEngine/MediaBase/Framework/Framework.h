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
* Framework.h
* This file for Media Framework define, here is the framework implementation
* and define the top level APIs for Media Application development.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef MEDIA_ENGINE_H
#define MEDIA_ENGINE_H

#include "ECType.h"
#include "MediaSource.h"
#include "VideoDecoder.h"
#include "AudioDecoder.h"
#include "VideoRender.h"
#include "AudioRender.h"
#include "MediaCommon.h"
#include "MediaMsgHandler.h"


class Framework : public MediaMsgHandler
{
public:
    Framework();
    ~Framework();
    EC_U32 OpenMedia(EC_CONST_PCHAR pFilePath, EC_VOIDP pVideoScreen);
    EC_VOID Play();
    EC_VOID Pause();
    EC_VOID Seek(EC_U32 nPostion);
    EC_VOID Stop();
    EC_VOID SetMediaNotify(MediaEngNotify *pNotify);
    EC_VOID GetMediaInfo(MediaEngMediaInfo *pMediaInfo);
    EC_U32 GetPlayStatus();
    EC_U32 GetMediaDuration();
    EC_U32 GetPlayingPosition();
    EC_VOID UpdateVideoScreen(EC_VOIDP pVideoScreen);

private:
    EC_VOID Reset();
    EC_VOID DoPlay();
    EC_VOID DoPause();
    EC_VOID DoSeek(EC_U32 nPostion);
    EC_VOID DoStop();
    EC_VOID DispatchMsg(void* pMsg = EC_NULL);
    EC_BOOL CheckStatusCanSwitch(MediaEngStatus nCurStatus,
                                 MediaEngStatus nNewStatus);
    static EC_S32 NotifyHandler(EC_VOIDP pUserData, EC_S32 nID,
                                EC_VOIDP pParam1, EC_VOIDP pParam2);
private:
    ECThread*           m_pThread;
    MediaSource*        m_pSource;
    AudioDecoder*       m_pAudioDecoder;
    VideoDecoder*       m_pVideoDecoder;
    AudioRender*        m_pAudioRender;
    VideoRender*        m_pVideoRender;
    MediaCtxInfo*       m_pMediaInfo;
    MediaClock*         m_pMediaClock;
    MediaEngNotify      m_sMediaNotify;
    MediaEngStatus      m_nStatus;
    MediaEngStatus      m_nPreStatus;
    EC_S32              m_nSeekPos;
    ECSemaphore         m_semFlushCompleted;
    ECSemaphore         m_semMediaEngStoped;
    EC_BOOL             m_bHasAudio;
    EC_BOOL             m_bHasVideo;
};

#endif /* MEDIA_ENGINE_H */