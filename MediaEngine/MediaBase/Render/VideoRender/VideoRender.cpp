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
* VideoRender.cpp
* This file for VideoRender class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECOSUtil.h"
#include "ECAutoLock.h"
#include "MediaSource.h"
#include "VideoRender.h"

#ifdef EC_OS_Win32
#include "SDL_VideoRender.h"
#elif defined EC_OS_Linux
/* TODO */
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
#include "iOS_VideoRender.h"
#elif defined EC_OS_Android
/* TODO */
#endif

VideoRender::VideoRender()
:m_nVideoWidth(0)
,m_nVideoHeight(0)
,m_nScreenWidth(0)
,m_nScreenHeight(0)
,m_pThread(EC_NULL)
,m_pMediaInfo(EC_NULL)
,m_pFrameScale(EC_NULL)
,m_pClockPort(EC_NULL)
,m_pVideoDecPort(EC_NULL)
,m_bNeedRender(EC_FALSE)
,m_pLatestRenderFrame(EC_NULL)
,m_pVideoRndDevice(EC_NULL)
,m_nStatus(MediaEngStatus_UnDefine)
{
    m_sEngineNotify.pUserData = EC_NULL;
    m_sEngineNotify.NotifyHandler = EC_NULL;
}

VideoRender::~VideoRender()
{
    if (m_pThread) delete m_pThread;
    if (m_pFrameScale) delete m_pFrameScale;
    if (m_pVideoRndDevice) delete m_pVideoRndDevice;
}

EC_U32 VideoRender::Init(MediaCtxInfo *pMediaInfo,
                         VideoDecPort* pVideoDecPort,
                         ClockPort* pClockPort, 
                         EC_VOIDP pVideoScreen,
                         MediaEngNotify *pNotify)
{
    if ((EC_NULL != pMediaInfo) &&
        (EC_NULL != pClockPort) &&
        (EC_NULL != pVideoScreen) &&
        (EC_NULL != pVideoDecPort) )
    {
        m_nVideoWidth = pMediaInfo->m_nVideoWidth;
        m_nVideoHeight = pMediaInfo->m_nVideoHeight;
        m_nScreenWidth = ((MediaEngVideoScreen*)pVideoScreen)->nWidth;
        m_nScreenHeight = ((MediaEngVideoScreen*)pVideoScreen)->nHeight;
        if ((m_nScreenWidth == 0) || (0 == m_nScreenHeight))
        {
            m_nScreenWidth = m_nVideoWidth;
            m_nScreenHeight = m_nVideoHeight;
        }

        m_pMediaInfo = pMediaInfo;
        m_pClockPort = pClockPort;
        m_pVideoDecPort = pVideoDecPort;
    }
    else return EC_Err_BadParam;
    
    // Init Render related resource.
    {
        ECAutoLock Lock(&m_mtxRender);
        /*Frame Scale Init*/
#ifdef EC_OS_Win32
        m_pFrameScale = new FrameScale();
#elif defined EC_OS_Linux
        /* TODO */
#elif defined EC_OS_MacOS
        /* TODO */
#elif defined EC_OS_iOS
        m_pFrameScale = new FrameScale(EC_FALSE);
#elif defined EC_OS_Android
        /* TODO */
#endif
        EC_U32 nRet = m_pFrameScale->Init(m_nVideoWidth,
                                          m_nVideoHeight,
                                          //m_nVideoWidth,
                                          //m_nVideoHeight,
                                          m_nScreenWidth,
                                          m_nScreenHeight,
                                          pMediaInfo->m_nFramePixFmt);
        if (EC_Err_None != nRet) return nRet;
        /*SDL Render Init*/
#ifdef EC_OS_Win32
        m_pVideoRndDevice = new SDL_VideoRender();
#elif defined EC_OS_Linux
        /* TODO */
#elif defined EC_OS_MacOS
        /* TODO */
#elif defined EC_OS_iOS
        m_pVideoRndDevice = new iOS_VideoRender();
#elif defined EC_OS_Android
        /* TODO */
#endif
        nRet = m_pVideoRndDevice->Init(pMediaInfo,
                                       m_nScreenWidth, m_nScreenHeight,
                                       ((MediaEngVideoScreen*)pVideoScreen)->pScreen);
        if (EC_Err_None != nRet) return nRet;
    }

    /*Render Thread Create*/
    m_pThread = new ECThread(this, (EC_PCHAR)"VideoRender");
    if (pNotify)
    {
        m_sEngineNotify.pUserData = pNotify->pUserData;
        m_sEngineNotify.NotifyHandler = pNotify->NotifyHandler;
    }

    m_bNeedRender = EC_TRUE;
    m_nStatus = MediaEngStatus_Inited;

    return Video_Render_Err_None;
}

EC_VOID VideoRender::Run()
{
    m_pThread->Run();
    m_pThread->PushMsg();
    m_nStatus = MediaEngStatus_Playing;
}

EC_VOID VideoRender::Pause()
{
    m_pThread->Pause();
    m_nStatus = MediaEngStatus_Pause;
}

EC_VOID VideoRender::Seek(EC_U32 nPos)
{
    m_pThread->ClearMsg();

    VideoFrame *pVideoFrame = EC_NULL;
    while (pVideoFrame ==EC_NULL)
    {
        m_pVideoDecPort->GetVideoFrame(&pVideoFrame);
    }

    /* Draw first seek frame on screen */
    {
        ECAutoLock Lock(&m_mtxRender);
        VideoFrame *pFrameYUV = EC_NULL;
        m_pFrameScale->Scale(pVideoFrame, &pFrameYUV);
        m_pVideoRndDevice->DrawFrame(pFrameYUV);
        if(m_pLatestRenderFrame)
            m_pVideoDecPort->ReturnVideoFrame(m_pLatestRenderFrame);
        m_pLatestRenderFrame = pVideoFrame;
    }
}

EC_VOID VideoRender::Stop()
{
    m_nStatus = MediaEngStatus_Stop;
    m_pVideoRndDevice->Stop();
    m_pThread->Stop();
    EC_U32 nID = MediaEngNotify_EngVRndStoped;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID VideoRender::Flush()
{
    MediaEngMsg *pMsg = new MediaEngMsg;
    pMsg->nCmd = MediaEngCommand_Flush;
    m_pThread->PushMsg(pMsg);
    m_nStatus = MediaEngStatus_Seeking;
}

EC_VOID VideoRender::Uninit()
{
    if (m_pLatestRenderFrame)
    {
        m_pVideoDecPort->ReturnVideoFrame(m_pLatestRenderFrame);
        m_pLatestRenderFrame = EC_NULL;
    }
    m_pFrameScale->Uninit();
    m_pVideoRndDevice->Uninit();
    m_nStatus = MediaEngStatus_UnDefine;
}

EC_VOID VideoRender::DispatchMsg(EC_VOIDP pMsg)
{
    if (pMsg)
        HandleControlMsg(pMsg);
    else
        RenderVideo();
}

/*Private Method*/
EC_VOID VideoRender::DoFlush()
{
    m_pThread->ClearMsg();

    if (m_pLatestRenderFrame)
    {
        m_pVideoDecPort->ReturnVideoFrame(m_pLatestRenderFrame);
        m_pLatestRenderFrame = EC_NULL;
    }

    EC_U32 ID = MediaEngNotify_VRndFlushCompleted;
    EC_VOIDP pUserData = m_sEngineNotify.pUserData;
    m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
}

EC_VOID VideoRender::RenderVideo()
{
    if (m_pLatestRenderFrame)
    {
        m_pVideoDecPort->ReturnVideoFrame(m_pLatestRenderFrame);
        m_pLatestRenderFrame = EC_NULL;
    }
    EC_U32 nRet = m_pVideoDecPort->GetVideoFrame(&m_pLatestRenderFrame);
    if (EC_NULL != m_pLatestRenderFrame)
    {
        /*Clock time sync check*/
        TimeStamp nTimeStampe = ((AVFrame*)m_pLatestRenderFrame)->pts;
        TimeStamp nWait = SyncClockTime(nTimeStampe);
        if( (0-nWait) < MAX_VIDEO_FRAME_DELAY)
        {
            if (nWait > 0) ecSleep((EC_U32)nWait);
            /*Render Video Frame*/
            VideoFrame *pFrameYUV = EC_NULL;
            if (m_bNeedRender)
            {
                ECAutoLock Lock(&m_mtxRender);
                m_pFrameScale->Scale(m_pLatestRenderFrame, &pFrameYUV);
                m_pVideoRndDevice->DrawFrame(pFrameYUV);
            }
        }
    }
    if(MediaEngStatus_Stop == m_nStatus)
    {
        return;
    }
    if (Media_VideoPlayback_EOS == nRet)
    {
        m_pThread->ClearMsg();
        m_pVideoRndDevice->ClearScreen();
        EC_U32 ID = MediaEngNotify_EngVRndPlayFinished;
        EC_VOIDP pUserData = m_sEngineNotify.pUserData;
        m_sEngineNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
    }
    else
        m_pThread->PushMsg();
}

EC_VOID VideoRender::HandleControlMsg(EC_VOIDP pMsg)
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

TimeStamp VideoRender::SyncClockTime(TimeStamp nTime)
{
    return (nTime - m_pClockPort->GetClockTime());
}

EC_VOID VideoRender::UpdateVideoScreen(EC_VOIDP pVideoScreen)
{
    if(EC_NULL != pVideoScreen)
    {
        MediaEngVideoScreen *pScreen = (MediaEngVideoScreen*)pVideoScreen;
        EC_U32 nWidth = pScreen->nWidth;
        EC_U32 nHeight = pScreen->nHeight;
        if ((nWidth == 0) || (nHeight == 0))
        {
            m_bNeedRender = EC_FALSE;
            return;
        }

        if (m_pFrameScale && m_pVideoRndDevice)
        {
            ECAutoLock Lock(&m_mtxRender);
            m_pFrameScale->UpdateVideoScreen((MediaEngVideoScreen*)pVideoScreen);
            m_pVideoRndDevice->UpdateVideoScreen((MediaEngVideoScreen*)pVideoScreen);

            if (EC_NULL != m_pLatestRenderFrame)
            {
                VideoFrame *pYUVFrame = EC_NULL;
                m_pFrameScale->Scale(m_pLatestRenderFrame, &pYUVFrame);
                m_pVideoRndDevice->DrawFrame(pYUVFrame);
            }
            m_bNeedRender = EC_TRUE;
        }
    }
    else m_bNeedRender = EC_FALSE;
}
