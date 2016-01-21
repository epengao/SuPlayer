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
* AudioRender.h
* This file for Media Audio Render class APIs define. Framework will send
* all the audio PCM buffers to here, and render the audio PCM buffers to the
* audio card.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef AUDIO_RENDER_H
#define AUDIO_RENDER_H

#include "ECType.h"
#include "Source.h"
#include "ECThread.h"
#include "VideoRend.h"
#include "ClockPort.h"
#include "AudioDecPort.h"
#include "AudioWaveScale.h"
#include "MediaMsgHandler.h"
#include "AudioRenderDeviceI.h"

class AudioRender : MediaMsgHandler
{
public:
    AudioRender();
    ~AudioRender();
public:
    EC_U32 Init(MediaCtxInfo *pMediaInfo,
                AudioDecPort* pAudioDecPort,
                ClockPort* pClockPort,
                MediaEngNotify *pNotify);
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Seek(EC_U32 nPos);
    EC_VOID Stop();
    EC_VOID Flush();
    EC_VOID Uninit();
    EC_VOID DispatchMsg(EC_VOIDP pMsg = EC_NULL);

private:
    EC_VOID DoFlush();
    EC_VOID RenderAudio();
    EC_VOID HandleControlMsg(EC_VOIDP pMsg);
private:
    ECThread*            m_pThread;
    EC_BOOL              m_isRenderInit;
    MediaCtxInfo*        m_pMediaInfo;
    AudioWaveScale*      m_pWaveScale;
    ClockPort*           m_pClockPort;
    AudioDecPort*        m_pAudioDecPort;
    MediaEngNotify       m_sEngineNotify;
    AudioRenderDeviceI*  m_pAudioRndDevice;
    MediaEngStatus       m_nStatus;
    EC_BOOL              m_bAudioFlushed;
};

#endif /* AUDIO_RENDER_H */