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
* VideoDecoder.cpp
* This file for Media video decoder module class implementaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "VideoDec.h"
#include "VideoDecPort.h"
#include "VideoDecoder.h"


VideoDecoder::VideoDecoder()
:m_bEOS(EC_FALSE)
,m_pPort(EC_NULL)
,m_pThread(EC_NULL)
,m_pFFmpegVideoDec(EC_NULL)
,m_pSourcePort(EC_NULL)
,m_pBufferManager(EC_NULL)
{
    m_sEngineNotify.pUserData = EC_NULL;
    m_sEngineNotify.NotifyHandler = EC_NULL;
}

VideoDecoder::~VideoDecoder()
{
    if (m_pPort) delete m_pPort;
    if (m_pThread) delete m_pThread;
    if (m_pBufferManager) delete m_pBufferManager;
    if (m_pFFmpegVideoDec) delete m_pFFmpegVideoDec;
}

EC_U32 VideoDecoder::Init(MediaCtxInfo* pMediaInfo,
                          SourcePort* pSourcePort,
                          MediaEngNotify* pNotify)
{
    if ((EC_NULL == pMediaInfo)|| 
        (EC_NULL == pSourcePort))
        return EC_Err_BadParam;

    m_pSourcePort = pSourcePort;
    m_pPort = new VideoDecPort(this);
    if (EC_NULL == m_pPort) return EC_Err_Memory_Low;

    m_pFFmpegVideoDec = new FFmpegVideoDec();
    if (m_pFFmpegVideoDec)
    {
        EC_U32 nRet = m_pFFmpegVideoDec->Init(pMediaInfo);
        if (EC_Err_None != nRet)
        {
            delete m_pPort; m_pPort = EC_NULL;
            delete m_pFFmpegVideoDec; m_pFFmpegVideoDec = EC_NULL;
            return nRet;
        }
    }
    else return EC_Err_Memory_Low;

    m_pBufferManager = new VideoFrameManager();
    if (EC_NULL == m_pBufferManager)
    {
        delete m_pPort; m_pPort = EC_NULL;
        delete m_pFFmpegVideoDec; m_pFFmpegVideoDec = EC_NULL;
        return EC_Err_Memory_Low;
    }

    m_pThread = new ECThread(this, (EC_PCHAR)"VideoDecoder");
    if (EC_NULL == m_pThread)
    {
        delete m_pPort; m_pPort = EC_NULL;
        delete m_pFFmpegVideoDec; m_pFFmpegVideoDec = EC_NULL;
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

EC_VOID VideoDecoder::Uninit()
{
    if (m_pThread) m_pThread->ClearMsg();
    if (m_pFFmpegVideoDec) m_pFFmpegVideoDec->Uninit();
    ClearAllBuffers();
}

EC_VOID VideoDecoder::Run()
{
    m_pThread->Run();
    m_pThread->PushMsg();
}

EC_VOID VideoDecoder::Pause()
{
    m_pThread->Pause();
}

EC_VOID VideoDecoder::Stop()
{
    m_pThread->Stop();
    EC_U32 nID = MediaEngNotify_EngVDecStoped;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID VideoDecoder::Flush()
{
    MediaEngMsg *pMsg = new MediaEngMsg;
    pMsg->nCmd = MediaEngCommand_Flush;
    m_pThread->PushMsg(pMsg);
}

VideoDecPort* VideoDecoder::GetVideoDecPort()
{
    return m_pPort;
}

EC_VOID VideoDecoder::DispatchMsg(EC_VOIDP pMsg)
{
    if (pMsg)
        HandleControlMsg(pMsg);
    else
        DecodeVideo();
}

EC_U32 VideoDecoder::GetVdieoFrame(VideoFrame** ppFrame)
{
    if (!m_bEOS)
    {
        EC_U32 nRet = m_pBufferManager->PopVideoFrame(ppFrame);
        if (EC_Err_None != nRet)
        {
            m_pThread->PushMsg();
            return Video_Dec_Err_NeedRetry;
        }
        return EC_Err_None;
    }
    else
    {
        m_pThread->ClearMsg();
        (*ppFrame) = EC_NULL;
        return Media_VideoPlayback_EOS;
    }
}

EC_VOID VideoDecoder::ReturnVdieoFrame(VideoFrame* pFrame)
{
    EC_U32 nRet = m_pBufferManager->PushReuseVideoFrame(pFrame);
    if (EC_Err_None != nRet)
    {
        m_pFFmpegVideoDec->ReleaseVideoFrame(pFrame);
    }
}

/* Private Method */
EC_VOID VideoDecoder::DoFlush()
{
    m_pThread->ClearMsg();
    VideoFrame* pFrame = EC_NULL;

    while (EC_Err_None == m_pBufferManager->PopVideoFrame(&pFrame))
        if (pFrame) ReturnVdieoFrame(pFrame);
    m_pFFmpegVideoDec->FlushVideoFrames();

    EC_U32 ID = MediaEngNotify_VDecFlushCompleted;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
}

EC_VOID VideoDecoder::DecodeVideo()
{
    if (!m_pBufferManager->IsVideoFrameQueueFull())
    {
        EC_U32 nRet = EC_Err_None;
        VideoFrame* pVideoFrame = EC_NULL;
        SourceBuffer* pSourceBuf = EC_NULL;
        nRet = m_pSourcePort->GetVideoBuffer(&pSourceBuf);
        if (pSourceBuf && (nRet == EC_Err_None))
        {
            VideoFrame *pTmpFrame = EC_NULL;
            nRet = m_pFFmpegVideoDec->DecodeVideo(pSourceBuf, &pTmpFrame);
            if (pTmpFrame && (EC_Err_None == nRet))
            {
                m_pBufferManager->PopReuseVideoFrame(&pVideoFrame);
                if (pVideoFrame == EC_NULL)
                {
                    pVideoFrame = m_pFFmpegVideoDec->AllocVideoFrame();
                }
                m_pFFmpegVideoDec->CopyVideoFrame(&pVideoFrame, pTmpFrame);
                if (EC_Err_None != m_pBufferManager->PushVideoFrame(pVideoFrame))
                {
                    m_pFFmpegVideoDec->ReleaseVideoFrame(pVideoFrame);
                }
            }
            m_pSourcePort->ReturnVideoBuffer(pSourceBuf);
        }
        else if (Media_VideoPlayback_EOS == nRet)
        {
            m_pThread->ClearMsg();
            m_bEOS = EC_TRUE;
        }
        else
            m_pThread->PushMsg();
    }
    else
    {
        m_pThread->ClearMsg();
    }
}

EC_VOID VideoDecoder::ClearAllBuffers()
{
    VideoFrame* pFrame = EC_NULL;
    while (EC_Err_None == m_pBufferManager->PopVideoFrame(&pFrame))
        if (pFrame) m_pFFmpegVideoDec->ReleaseVideoFrame(pFrame);
    while (EC_Err_None == m_pBufferManager->PopReuseVideoFrame(&pFrame))
        if (pFrame) m_pFFmpegVideoDec->ReleaseVideoFrame(pFrame);
}

EC_VOID VideoDecoder::HandleControlMsg(EC_VOIDP pMsg)
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

