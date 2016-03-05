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
* MediaSource.cpp
* This file for Media data source implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECOSUtil.h"
#include "SourcePort.h"
#include "ECAutoLock.h"
#include "MediaSource.h"

#define PURE_AUDIO_AVPKT_COUNT 8


MediaSource::MediaSource()
:m_pPort(EC_NULL)
,m_pThread(EC_NULL)
,m_pMediaInfo(EC_NULL)
,m_bEndOfSource(EC_FALSE)
,m_pFFmpegReader(EC_NULL)
,m_pBufferManager(EC_NULL)
{
    m_sEngineNotify.pUserData = EC_NULL;
    m_sEngineNotify.NotifyHandler = EC_NULL;
}

MediaSource::~MediaSource()
{
    if (m_pPort) delete m_pPort;
    if (m_pThread) delete m_pThread;
    if (m_pMediaInfo) delete m_pMediaInfo;
    if (m_pFFmpegReader) delete m_pFFmpegReader;
    if (m_pBufferManager) delete m_pBufferManager;
}

EC_U32 MediaSource::Init(EC_CONST_PCHAR pMediaPath, MediaEngNotify *pNotify)
{
    if (EC_NULL == pMediaPath) return EC_Err_BadParam;
    m_pFFmpegReader = new FFmpegReader(pMediaPath);
    if (m_pFFmpegReader)
    {
        EC_U32 nRet = m_pFFmpegReader->Init();
        if (Source_Err_None != nRet) return nRet;
        m_pMediaInfo = new MediaCtxInfo();
        nRet = m_pFFmpegReader->GetMediaInfo(&m_pMediaInfo);
        if (Source_Err_None != nRet)
        {
            delete m_pMediaInfo;
            m_pMediaInfo = EC_NULL;
        }
    }
    else return EC_Err_Memory_Low;

    if (m_pMediaInfo->m_nVideoIndex < 0)
        m_pBufferManager = new SourceBufferManager(PURE_AUDIO_AVPKT_COUNT);
    else
        m_pBufferManager = new SourceBufferManager();
    if (EC_NULL == m_pBufferManager) return EC_Err_Memory_Low;

    m_pThread = new ECThread(this, (EC_PCHAR)"MediaSource");
    if (EC_NULL == m_pThread) return EC_Err_Memory_Low;

    m_pPort = new SourcePort(this);
    if (EC_NULL == m_pPort) return EC_Err_Memory_Low;

    if (pNotify)
    {
        m_sEngineNotify.pUserData = pNotify->pUserData;
        m_sEngineNotify.NotifyHandler = pNotify->NotifyHandler;
    }

    return Source_Err_None;
}

EC_VOID MediaSource::Run()
{
    m_pThread->Run();
    m_pThread->PushMsg();
}

EC_VOID MediaSource::Pause()
{
    m_pThread->Pause();
}

EC_VOID MediaSource::Seek(EC_U32 nPos)
{
    m_pFFmpegReader->Seek(nPos);
}

EC_VOID MediaSource::Stop()
{
    m_pThread->Stop();
    EC_U32 nID = MediaEngNotify_EngSrcStoped;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID MediaSource::Flush()
{
    MediaEngMsg *pMsg = new MediaEngMsg;
    pMsg->nCmd = MediaEngCommand_Flush;
    m_pThread->PushMsg(pMsg);
}

EC_VOID MediaSource::Uninit()
{
    ClearAllBuffers();
    if (m_pThread) m_pThread->ClearMsg();
    if (m_pFFmpegReader) m_pFFmpegReader->Uninit();
}

MediaCtxInfo* MediaSource::GetMediaInfo()
{
    return m_pMediaInfo;
}

SourcePort* MediaSource::GetSourcePort()
{
    return m_pPort;
}

EC_VOID MediaSource::DispatchMsg(EC_VOIDP pMsg)
{
    if (pMsg)
        HandleControlMsg(pMsg);
    else
        ReadSourceBuffer();
}

EC_U32 MediaSource::GetVdieoBuffer(SourceBuffer** ppBuffer)
{
    EC_U32 nRet = m_pBufferManager->PopVideoBuffer(ppBuffer);
    if (EC_Err_None != nRet)
    {
        if (m_bEndOfSource)
        {
            /* Here we need report to Framework */
            m_pThread->ClearMsg();
            return Media_VideoPlayback_EOS;
        }
        else
        {
            m_pThread->PushMsg();
            return Source_Err_NeedRetry;
        }
    }
    return EC_Err_None;
}

EC_VOID MediaSource::ReturnVideoBuffer(SourceBuffer* pBuffer)
{
    EC_U32 nRet;
    m_pFFmpegReader->ReleaseSourceBuffer(pBuffer);
    nRet = m_pBufferManager->PushReuseVideoBuffer(pBuffer);
    if (EC_Err_None != nRet)
    {
        av_free(pBuffer);
    }
}

EC_U32 MediaSource::GetAudioBuffer(SourceBuffer** ppBuffer)
{
    EC_U32 nRet = m_pBufferManager->PopAudioBuffer(ppBuffer);
    if (EC_Err_None != nRet)
    {
        if (m_bEndOfSource)
        {
            /* Here we need report to Framework */
            m_pThread->ClearMsg();
            return Media_AudioPlayback_EOS;
        }
        else
        {
            m_pThread->PushMsg();
            return Source_Err_NeedRetry;
        }
    }
    return EC_Err_None;
}

EC_VOID MediaSource::ReturnAudioBuffer(SourceBuffer* pBuffer)
{
    EC_U32 nRet;
    m_pFFmpegReader->ReleaseSourceBuffer(pBuffer);
    nRet = m_pBufferManager->PushReuseAudioBuffer(pBuffer);
    if (EC_Err_None != nRet)
    {
        av_free(pBuffer);
    }
}

/* Private Method */
EC_VOID MediaSource::DoFlush()
{
    m_pThread->ClearMsg();
    SourceBuffer* pBuf = EC_NULL;
    /* Video */
    while (EC_Err_None == m_pBufferManager->PopVideoBuffer(&pBuf))
        if (pBuf) ReturnVideoBuffer(pBuf);
    /* Audio */
    while (EC_Err_None == m_pBufferManager->PopAudioBuffer(&pBuf))
        if (pBuf) ReturnAudioBuffer(pBuf);

    EC_U32 ID = MediaEngNotify_SrcFlushCompleted;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
}

EC_VOID MediaSource::ReadSourceBuffer()
{
    if (!m_pBufferManager->IsVideoBufferQueueFull() &&
        !m_pBufferManager->IsAudioBufferQueueFull() )
    {
        SourceBuffer* pBuff = EC_NULL;
        m_pBufferManager->PopReuseVideoBuffer(&pBuff);

        EC_U32 nRet = m_pFFmpegReader->ReadSourceBuffer(&pBuff);
        if (Source_Err_Read_Video == nRet)
        {
            nRet = m_pBufferManager->PushVideoBuffer(pBuff);
            if (EC_Err_None != nRet) av_free(pBuff);
        }
        else if (Source_Err_Read_Audio == nRet)
        {
            nRet = m_pBufferManager->PushAudioBuffer(pBuff);
            if (EC_Err_None != nRet) av_free(pBuff);
        }
        else
        {
            if (pBuff)
            {
                m_pFFmpegReader->ReleaseSourceBuffer(pBuff);
            }
            if (Source_Err_EndOfSource == nRet)
            {
                m_bEndOfSource = EC_TRUE;
                return;
            }
        }
        m_pThread->PushMsg();
    }
    else
    {
        m_pThread->ClearMsg();
    }
}

EC_VOID MediaSource::HandleControlMsg(EC_VOIDP pMsg)
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

EC_VOID MediaSource::ClearAllBuffers()
{
    SourceBuffer* pBuf = EC_NULL;
    /* Video */
    while (EC_Err_None == m_pBufferManager->PopVideoBuffer(&pBuf))
        if (pBuf)
        {
            m_pFFmpegReader->ReleaseSourceBuffer(pBuf);
            av_free(pBuf);
        }
    while (EC_Err_None == m_pBufferManager->PopReuseVideoBuffer(&pBuf))
        if (pBuf)
        {
            m_pFFmpegReader->ReleaseSourceBuffer(pBuf);
            av_free(pBuf);
        }
    /* Audio */
    while (EC_Err_None == m_pBufferManager->PopAudioBuffer(&pBuf))
        if (pBuf)
        {
            m_pFFmpegReader->ReleaseSourceBuffer(pBuf);
            av_free(pBuf);
        }
    while (EC_Err_None == m_pBufferManager->PopReuseAudioBuffer(&pBuf))
        if (pBuf)
        {
            m_pFFmpegReader->ReleaseSourceBuffer(pBuf);
            av_free(pBuf);
        }
}

