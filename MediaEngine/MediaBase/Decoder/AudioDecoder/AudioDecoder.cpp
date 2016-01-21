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
* AudioDecoder.cpp
* This file for Media audio decoder module class implementaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "AudioDec.h"
#include "AudioDecPort.h"
#include "AudioDecoder.h"


AudioDecoder::AudioDecoder()
:m_bEOS(EC_FALSE)
,m_pPort(EC_NULL)
,m_pThread(EC_NULL)
,m_pFFmpegAudioDec(EC_NULL)
,m_pSourcePort(EC_NULL)
,m_pBufferManager(EC_NULL)
{
    m_sEngineNotify.pUserData = EC_NULL;
    m_sEngineNotify.NotifyHandler = EC_NULL;
}

AudioDecoder::~AudioDecoder()
{
    if (m_pPort) delete m_pPort;
    if (m_pThread) delete m_pThread;
    if (m_pBufferManager) delete m_pBufferManager;
    if (m_pFFmpegAudioDec) delete m_pFFmpegAudioDec;
}

EC_U32 AudioDecoder::Init(MediaCtxInfo* pMediaInfo,
                          SourcePort* pSourcePort,
                          MediaEngNotify *pNotify)
{
    if ((EC_NULL == pMediaInfo)|| 
        (EC_NULL == pSourcePort))
        return EC_Err_BadParam;

    m_pSourcePort = pSourcePort;
    m_pPort = new AudioDecPort(this);
    if (EC_NULL == m_pPort) return EC_Err_Memory_Low;

    m_pFFmpegAudioDec = new FFmpegAudioDec();
    if (m_pFFmpegAudioDec)
    {
        EC_U32 nRet = m_pFFmpegAudioDec->Init(pMediaInfo);
        if (EC_Err_None != nRet)
        {
            delete m_pPort; m_pPort = EC_NULL;
            delete m_pFFmpegAudioDec; m_pFFmpegAudioDec = EC_NULL;
            return nRet;
        }
    }
    else return EC_Err_Memory_Low;

    m_pBufferManager = new AudioPCMBufferManager();
    if (EC_NULL == m_pBufferManager)
    {
        delete m_pPort; m_pPort = EC_NULL;
        delete m_pFFmpegAudioDec; m_pFFmpegAudioDec = EC_NULL;
        return EC_Err_Memory_Low;
    }

    m_pThread = new ECThread(this, (EC_PCHAR)"AudioDecoder");
    if (EC_NULL == m_pThread)
    {
        delete m_pPort; m_pPort = EC_NULL;
        delete m_pFFmpegAudioDec; m_pFFmpegAudioDec = EC_NULL;
        delete m_pBufferManager; m_pBufferManager = EC_NULL;
        return EC_Err_Memory_Low;
    }

    if (pNotify)
    {
        m_sEngineNotify.pUserData = pNotify->pUserData;
        m_sEngineNotify.NotifyHandler = pNotify->NotifyHandler;
    }

    return Source_Err_None;
}

EC_VOID AudioDecoder::Uninit()
{
    if (m_pThread) m_pThread->ClearMsg();
    if (m_pFFmpegAudioDec) m_pFFmpegAudioDec->Uninit();
    ClearAllBuffers();
}

EC_VOID AudioDecoder::Run()
{
    m_pThread->Run();
    m_pThread->PushMsg();
}

EC_VOID AudioDecoder::Pause()
{
    m_pThread->Pause();
}

EC_VOID AudioDecoder::Stop()
{
    m_pThread->Stop();
    EC_U32 nID = MediaEngNotify_EngADecStoped;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID AudioDecoder::Flush()
{
    MediaEngMsg *pMsg = new MediaEngMsg;
    pMsg->nCmd = MediaEngCommand_Flush;
    m_pThread->PushMsg(pMsg);
}

AudioDecPort* AudioDecoder::GetAudioDecPort()
{
    return m_pPort;
}

EC_VOID AudioDecoder::DispatchMsg(EC_VOIDP pMsg)
{
    if (pMsg)
        HandleControlMsg(pMsg);
    else
        DecodeAudio();
}

EC_U32 AudioDecoder::GetAudioPCMBuffer(AudioPCMBuffer** ppBuffer)
{
    if (!m_bEOS)
    {
        EC_U32 nRet = m_pBufferManager->PopAudioPCMBuffer(ppBuffer);
        if (EC_Err_None != nRet)
        {
            m_pThread->PushMsg();
            return Audio_Dec_Err_NeedRetry;
        }
        return EC_Err_None;
    }
    else
    {
        (*ppBuffer) = EC_NULL;
        m_pThread->ClearMsg();
        return Media_AudioPlayback_EOS;
    }
}

EC_VOID AudioDecoder::ReturnAudioPCMBuffer(AudioPCMBuffer* pBuffer)
{
    EC_U32 nRet = m_pBufferManager->PushReuseAudioPCMBuffer(pBuffer);
    if (EC_Err_None != nRet)
    {
        m_pFFmpegAudioDec->ReleaseAudioPCMBuffer(pBuffer);
    }
}

/* Private Method */
EC_VOID AudioDecoder::DoFlush()
{
    m_pThread->ClearMsg();
    AudioPCMBuffer* pBuf = EC_NULL;

    while (EC_Err_None == m_pBufferManager->PopAudioPCMBuffer(&pBuf))
        if (pBuf) ReturnAudioPCMBuffer(pBuf);
    m_pFFmpegAudioDec->FlushAuidoPCMBufs();

    EC_U32 ID = MediaEngNotify_ADecFlushCompleted;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
}

EC_VOID AudioDecoder::DecodeAudio()
{
    if (!m_pBufferManager->IsAudioPCMBufferQueueFull())
    {
        EC_U32 nRet = EC_Err_None;
        SourceBuffer* pSourceBuf = EC_NULL;
        AudioPCMBuffer* pAudioPCMBuf = EC_NULL;

        nRet = m_pSourcePort->GetAudioBuffer(&pSourceBuf);
        if (pSourceBuf && (EC_Err_None == nRet))
        {
            AudioPCMBuffer* pTmpPCMBuf = EC_NULL;
            nRet = m_pFFmpegAudioDec->DecodeAudio(pSourceBuf, &pTmpPCMBuf);
            if (pTmpPCMBuf && (EC_Err_None == nRet))
            {
                m_pBufferManager->PopReuseAudioPCMBuffer(&pAudioPCMBuf);
                if (pAudioPCMBuf == EC_NULL)
                {
                    pAudioPCMBuf = m_pFFmpegAudioDec->AllocAudioPCMBuffer();
                }
                m_pFFmpegAudioDec->CopyAudioPCMBuffer(&pAudioPCMBuf, pTmpPCMBuf);
                if (EC_Err_None != m_pBufferManager->PushAudioPCMBuffer(pAudioPCMBuf))
                {
                    m_pFFmpegAudioDec->ReleaseAudioPCMBuffer(pAudioPCMBuf);
                }
            }
            m_pSourcePort->ReturnAudioBuffer(pSourceBuf);
        }
        else if (Media_AudioPlayback_EOS == nRet)
        {
            m_pThread->ClearMsg();
            m_bEOS = EC_TRUE;
        }
        else
            m_pThread->PushMsg();
    }
    else
        m_pThread->ClearMsg();
}

EC_VOID AudioDecoder::ClearAllBuffers()
{
    AudioPCMBuffer* pBuf = EC_NULL;
    while (EC_Err_None == m_pBufferManager->PopAudioPCMBuffer(&pBuf))
        if (pBuf) m_pFFmpegAudioDec->ReleaseAudioPCMBuffer(pBuf);
    while (EC_Err_None == m_pBufferManager->PopReuseAudioPCMBuffer(&pBuf))
        if (pBuf) m_pFFmpegAudioDec->ReleaseAudioPCMBuffer(pBuf);
}

EC_VOID AudioDecoder::HandleControlMsg(EC_VOIDP pMsg)
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
