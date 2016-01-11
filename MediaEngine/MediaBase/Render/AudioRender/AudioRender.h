/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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