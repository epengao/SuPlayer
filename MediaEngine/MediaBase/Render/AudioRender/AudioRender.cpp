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
* AudioRender.cpp
* This file for AudioRender class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECMemOP.h"
#include "ECOSUtil.h"
#include "MediaSource.h"
#include "AudioRender.h"

#ifdef EC_OS_Win32
#include "SDL_AudioRender.h"
#elif defined EC_OS_Linux
/* TODO */
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
#include "iOS_AudioRender.h"
#elif defined EC_OS_Android
/* TODO */
#endif


AudioRender::AudioRender()
:m_pThread(EC_NULL)
,m_isRenderInit(EC_FALSE)
,m_pMediaInfo(EC_NULL)
,m_pWaveScale(EC_NULL)
,m_pClockPort(EC_NULL)
,m_pAudioDecPort(EC_NULL)
,m_pAudioRndDevice(EC_NULL)
,m_nStatus(MediaEngStatus_Inited)
,m_bAudioFlushed(EC_FALSE)
{
    m_sEngineNotify.pUserData = EC_NULL;
    m_sEngineNotify.NotifyHandler = EC_NULL;
}

AudioRender::~AudioRender()
{
    if (m_pThread) delete m_pThread;
    if (m_pWaveScale) delete m_pWaveScale;
    if (m_pAudioRndDevice) delete m_pAudioRndDevice;
}

EC_U32 AudioRender::Init(MediaCtxInfo *pMediaInfo,
                         AudioDecPort* pAudioDecPort,
                         ClockPort* pClockPort,
                         MediaEngNotify *pNotify)
{
    if ((EC_NULL != pMediaInfo) &&
        (EC_NULL != pAudioDecPort) &&
        (EC_NULL != pClockPort))
    {
        m_pMediaInfo = pMediaInfo;
        m_pClockPort = pClockPort;
        m_pAudioDecPort = pAudioDecPort;
    }
    else return EC_Err_BadParam;

    /*Render Thread Create*/
    m_pThread = new ECThread(this, (EC_PCHAR)"AudioRender");
    if (EC_NULL == m_pThread) return EC_Err_Memory_Low;

    if (pNotify)
    {
        m_sEngineNotify.pUserData = pNotify->pUserData;
        m_sEngineNotify.NotifyHandler = pNotify->NotifyHandler;
    }

    return Video_Render_Err_None;
}

EC_VOID AudioRender::Run()
{
    m_pThread->Run();
    m_pThread->PushMsg();
    if (m_isRenderInit)
    {
        m_pClockPort->Run();
        m_pAudioRndDevice->Run();
    }
}

EC_VOID AudioRender::Pause()
{
    m_pThread->Pause();
    m_pClockPort->Pause();
    m_pAudioRndDevice->Pause();
}

EC_VOID AudioRender::Seek(EC_U32 nPos)
{
    m_pThread->ClearMsg();
    m_bAudioFlushed = EC_TRUE;
    TimeStamp timestamp = 0;
    AudioPCMBuffer *pBuf = EC_NULL;
    //while (timestamp < nPos)
    while (pBuf == EC_NULL)
    {
        m_pAudioDecPort->GetAudioPCMBuffer(&pBuf);
        if(pBuf)
        {
            timestamp = ((AVFrame*)pBuf)->pts;
            m_pAudioDecPort->ReturnAudioPCMBuffer(pBuf);
        }
    }
    m_pClockPort->UpdateClockTime(timestamp);
}

EC_VOID AudioRender::Stop()
{
    m_nStatus = MediaEngStatus_Stop;
    m_pThread->ClearMsg();
    m_pAudioRndDevice->Stop();
    m_pThread->Stop();

    EC_U32 nID = MediaEngNotify_EngARndStoped;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID AudioRender::Flush()
{
    MediaEngMsg *pMsg = new MediaEngMsg;
    pMsg->nCmd = MediaEngCommand_Flush;
    m_pThread->PushMsg(pMsg);
}

EC_VOID AudioRender::Uninit()
{
    if(m_pWaveScale) m_pWaveScale->Uninit();
    if (m_pAudioRndDevice)m_pAudioRndDevice->Uninit();
}

EC_VOID AudioRender::DispatchMsg(EC_VOID* pMsg)
{
    if (pMsg)
        HandleControlMsg(pMsg);
    else
        RenderAudio();
}

/*Private Method*/
EC_VOID AudioRender::DoFlush()
{
    m_pThread->ClearMsg();
    m_pAudioRndDevice->Flush();

    EC_U32 nID = MediaEngNotify_ARndFlushCompleted;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID AudioRender::RenderAudio()
{
    AudioPCMBuffer *pBuf = EC_NULL;
    EC_U32 nRet = m_pAudioDecPort->GetAudioPCMBuffer(&pBuf);
    if (EC_NULL != pBuf)
    {
        if (!m_isRenderInit)
        {
            /*Frame Scale Init*/
            AudioPCMBuffer *pFirstFrame = pBuf;
            m_pWaveScale = new AudioWaveScale();
            EC_U32 nRet = m_pWaveScale->Init(m_pMediaInfo, pFirstFrame);
            if (EC_Err_None != nRet)
            {
                /* Report to FrameWork*/
                return;
            }
            /*SDL Render Init*/
#ifdef EC_OS_Win32
            m_pAudioRndDevice = new SDL_AudioRender();
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
            m_pAudioRndDevice = new iOS_AudioRender();
#elif defined EC_OS_Android
    /* TODO */
#endif
            nRet = m_pAudioRndDevice->Init(m_pMediaInfo, pFirstFrame);
            if (EC_Err_None != nRet)
            {
                /* Report to FrameWork*/
                return;
            }
            m_pAudioRndDevice->Run();
            m_isRenderInit = EC_TRUE;
        }

        EC_U32 nSize = 0;
        TimeStamp timestamp = ((AVFrame*)pBuf)->pts;
        AudioPCMBuffer *pPCMBuf = EC_NULL;
        m_pWaveScale->Scale(pBuf, &pPCMBuf, &nSize);
        if (EC_NULL != pPCMBuf)
        {
            m_pAudioRndDevice->SendPCMData(pPCMBuf, nSize);
            if (m_bAudioFlushed)
            {
                m_bAudioFlushed = EC_FALSE;
            }
            else
            {
                m_pClockPort->UpdateClockTime(timestamp);
            }
        }
        m_pAudioDecPort->ReturnAudioPCMBuffer(pBuf);
    }
    if (Media_AudioPlayback_EOS == nRet)
    {
        m_pThread->ClearMsg();
        m_pAudioRndDevice->Stop();
        EC_U32 ID = MediaEngNotify_EngARndPlayFinished;
        EC_VOIDP pUserData = m_sEngineNotify.pUserData;
        m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
    }
    if (MediaEngStatus_Stop == m_nStatus)
    {
        m_pThread->ClearMsg();
        return;
    }
    else
        m_pThread->PushMsg();
}

EC_VOID AudioRender::HandleControlMsg(EC_VOIDP pMsg)
{
    MediaEngMsg *pMessage = (MediaEngMsg*)pMsg;
    switch (pMessage->nCmd)
    {
        case MediaEngCommand_Flush:
        {
            DoFlush();
            break;
        }
        default: break;
    }
}
