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
* Framework.cpp
* This file for Framework class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECMemOP.h"
#include "Framework.h"
#include "ECOSUtil.h"


Framework::Framework()
:m_pThread(EC_NULL)
,m_pSource(EC_NULL)
,m_pAudioDecoder(EC_NULL)
,m_pVideoDecoder(EC_NULL)
,m_pAudioRender(EC_NULL)
,m_pVideoRender(EC_NULL)
,m_pMediaInfo(EC_NULL)
,m_pMediaClock(EC_NULL)
,m_nStatus(MediaEngStatus_UnDefine)
,m_nPreStatus(MediaEngStatus_UnDefine)
,m_nSeekPos(-1)
,m_semFlushCompleted(0, 1)
,m_semMediaEngStoped(0, 1)
,m_bHasAudio(EC_FALSE)
,m_bHasVideo(EC_FALSE)
{
    m_sMediaNotify.pUserData = EC_NULL;
    m_sMediaNotify.NotifyHandler = EC_NULL;
    m_pThread = new ECThread(this, (EC_PCHAR)"Framework");
    m_nStatus = MediaEngStatus_Inited;
    m_nPreStatus = MediaEngStatus_Inited;
}

Framework::~Framework()
{
    if (m_pThread)
    {
        m_pThread->ClearMsg();
        m_pThread->Stop();
    }

    if ((m_nStatus != MediaEngStatus_Stop) &&
        (m_nStatus != MediaEngStatus_Inited))
    {
        DoStop();
    }

    if (m_pSource) delete m_pSource;
    if (m_pAudioDecoder) delete m_pAudioDecoder;
    if (m_pVideoDecoder) delete m_pVideoDecoder;
    if (m_pAudioRender) delete m_pAudioRender;
    if (m_pVideoRender) delete m_pVideoRender;
    if (m_pMediaClock) delete m_pMediaClock;
    if (m_pThread) delete m_pThread;
}

EC_U32 Framework::OpenMedia(EC_CONST_PCHAR pFilePath, EC_VOIDP pVideoScreen)
{
    if(!CheckStatusCanSwitch(m_nStatus, MediaEngStatus_MediaOpend))
        return MediaEng_Err_NotInit;
    m_nPreStatus = m_nStatus;
    m_nStatus = MediaEngStatus_Switching;

    EC_U32 nRet;
    MediaEngNotify sNotify;
    sNotify.pUserData = this;
    sNotify.NotifyHandler = NotifyHandler;

    m_pSource = new MediaSource();
    nRet = m_pSource->Init(pFilePath, &sNotify);
    if (EC_Err_None != nRet) return nRet;

    m_pMediaInfo = (MediaCtxInfo*)m_pSource->GetMediaInfo();
    m_bHasAudio = (m_pMediaInfo->m_nAudioIndex != -1);
    m_bHasVideo = (m_pMediaInfo->m_nVideoIndex != -1);

    if (!m_bHasAudio && !m_bHasVideo)
        return MediaEng_Err_FileNotSupport;

    m_pMediaClock = new MediaClock();
    if (m_bHasAudio)
    {
        m_pAudioDecoder = new AudioDecoder();
        nRet = m_pAudioDecoder->Init(m_pMediaInfo,
            m_pSource->GetSourcePort(), &sNotify);
        if (EC_Err_None != nRet) return nRet;

        m_pAudioRender = new AudioRender();
        nRet = m_pAudioRender->Init(m_pMediaInfo,
            m_pAudioDecoder->GetAudioDecPort(),
            m_pMediaClock->GetClockPort(), &sNotify);
        if (EC_Err_None != nRet) return nRet;
    }
    if (m_bHasVideo)
    {
        m_pVideoDecoder = new VideoDecoder();
        nRet = m_pVideoDecoder->Init(m_pMediaInfo,
            m_pSource->GetSourcePort(), &sNotify);
        if (EC_Err_None != nRet) return nRet;

        m_pVideoRender = new VideoRender();
        nRet = m_pVideoRender->Init(m_pMediaInfo,
            m_pVideoDecoder->GetVideoDecPort(),
            m_pMediaClock->GetClockPort(),
            pVideoScreen, &sNotify);
        if (EC_Err_None != nRet) return nRet;
    }

    m_pThread->Run();
    m_nStatus = MediaEngStatus_MediaOpend;

    return EC_Err_None;
}

EC_VOID Framework::Play()
{
    if (CheckStatusCanSwitch(m_nStatus, MediaEngStatus_Playing))
    {
        m_nPreStatus = m_nStatus;
        m_nStatus = MediaEngStatus_Switching;
        MediaEngMsg *pMsg = new MediaEngMsg;
        pMsg->nCmd = MediaEngCommand_Play;
        m_pThread->PushMsg(pMsg);
    }
}

EC_VOID Framework::Pause()
{
    if (CheckStatusCanSwitch(m_nStatus, MediaEngStatus_Pause))
    {
        m_nPreStatus = m_nStatus;
        m_nStatus = MediaEngStatus_Switching;
        MediaEngMsg *pMsg = new MediaEngMsg;
        pMsg->nCmd = MediaEngCommand_Pause;
        m_pThread->PushMsg(pMsg);
    }
}

EC_VOID Framework::Seek(EC_U32 nPostion)
{
    if((nPostion >= m_pMediaInfo->m_nDuration) ||
       (nPostion <= 0)) return;

    if (CheckStatusCanSwitch(m_nStatus, MediaEngStatus_Seeking))
    {
        m_nPreStatus = m_nStatus;
        m_nStatus = MediaEngStatus_Seeking;
        m_nSeekPos = nPostion;
        MediaEngMsg *pMsg = new MediaEngMsg;
        pMsg->nCmd = MediaEngCommand_Seek;
        pMsg->pParam = new EC_U32(m_nSeekPos);
        m_pThread->PushMsg(pMsg);
    }
}

EC_VOID Framework::Stop()
{
    if (CheckStatusCanSwitch(m_nStatus, MediaEngStatus_Stop))
    {
        m_nPreStatus = m_nStatus;
        m_nStatus = MediaEngStatus_Switching;
        MediaEngMsg *pMsg = new MediaEngMsg;
        pMsg->nCmd = MediaEngCommand_Stop;
        m_pThread->PushMsg(pMsg);
    }
}

EC_VOID Framework::SetMediaNotify(MediaEngNotify *pNotify)
{
    m_sMediaNotify.pUserData = pNotify->pUserData;
    m_sMediaNotify.NotifyHandler = pNotify->NotifyHandler;
}

EC_VOID Framework::GetMediaInfo(MediaEngMediaInfo *pMediaInfo)
{
    pMediaInfo->nWidth = m_pMediaInfo->m_nVideoWidth;
    pMediaInfo->nHeight = m_pMediaInfo->m_nVideoHeight;
    pMediaInfo->nDuration = m_pMediaInfo->m_nDuration;
}

EC_U32 Framework::GetPlayStatus()
{
    if((m_nStatus == MediaEngStatus_Seeking) ||
       (m_nStatus == MediaEngStatus_Seeking))
        return (EC_U32)m_nPreStatus;
    else
        return (EC_U32)m_nStatus;
}

EC_U32 Framework::GetMediaDuration()
{
    return (m_pMediaInfo->m_nDuration);
}

EC_U32 Framework::GetPlayingPosition()
{
    EC_U32 nPos = (EC_U32)m_pMediaClock->GetClockTime();
    if (nPos > m_pMediaInfo->m_nDuration)
        nPos = m_pMediaInfo->m_nDuration;
    return nPos;
}

EC_VOID Framework::Reset()
{
    if (m_pAudioRender)
    {
        m_pAudioRender->Uninit();
        delete m_pAudioRender;
        m_pAudioRender = EC_NULL;
    }
    if (m_pVideoRender)
    {
        m_pVideoRender->Uninit();
        delete m_pVideoRender;
        m_pVideoRender = EC_NULL;
    }
    if (m_pAudioDecoder)
    {
        m_pAudioDecoder->Uninit();
        delete m_pAudioDecoder;
        m_pAudioDecoder = EC_NULL;
    }
    if (m_pVideoDecoder) 
    {
        m_pVideoDecoder->Uninit();
        delete m_pVideoDecoder;
        m_pVideoDecoder = EC_NULL;
    }
    if (m_pMediaClock)
    {
        delete m_pMediaClock;
        m_pMediaClock = EC_NULL;
    }
    if (m_pSource)
    {
        m_pSource->Uninit();
        delete m_pSource;
        m_pSource = EC_NULL;
    }
}

EC_VOID Framework::UpdateVideoScreen(EC_VOIDP pVideoScreen)
{
    if (m_pVideoRender)
    {
        m_pVideoRender->UpdateVideoScreen(pVideoScreen);
    }
}

/* Private Methods */
EC_VOID Framework::DoPlay()
{
    if (m_pSource) m_pSource->Run();
    //Sleep(20);
    if (m_pAudioDecoder) m_pAudioDecoder->Run();
    if (m_pVideoDecoder) m_pVideoDecoder->Run();
    //Sleep(20);
    if (m_pAudioRender) m_pAudioRender->Run();
    if (m_pVideoRender) m_pVideoRender->Run();
    if (m_pMediaClock) m_pMediaClock->Run();
    m_nStatus = MediaEngStatus_Playing;
}

EC_VOID Framework::DoPause()
{
    if (m_pMediaClock) m_pMediaClock->Pause();
    if (m_pAudioRender) m_pAudioRender->Pause();
    if (m_pVideoRender) m_pVideoRender->Pause();

    m_nStatus = MediaEngStatus_Pause;
}

EC_VOID Framework::DoSeek(EC_U32 nPostion)
{
    /* Pause curr playback */
    if (m_pMediaClock) m_pMediaClock->Pause();
    if (m_pAudioRender) m_pAudioRender->Pause();
    if (m_pVideoRender) m_pVideoRender->Pause();
    /* Start Flush A/V buffers, and wait complete */
    if (m_pAudioDecoder) m_pAudioDecoder->Flush();
    if (m_pVideoDecoder) m_pVideoDecoder->Flush();
    if (m_pSource) m_pSource->Flush();
    /* Wait flush compeleted */
    m_semFlushCompleted.WaitSIGNAL();
    /* Fast run to the wanted seek pos */
    if (m_pSource) m_pSource->Seek(nPostion);
    if (m_pAudioRender) m_pAudioRender->Seek(nPostion);
    if (m_pVideoRender) m_pVideoRender->Seek(nPostion);
    /* If pre status is playing, restore it */
    if(MediaEngStatus_Playing == m_nPreStatus)
    {
        if (m_pMediaClock) m_pMediaClock->Run();
        if (m_pAudioRender) m_pAudioRender->Run();
        if (m_pVideoRender) m_pVideoRender->Run();
    }
    m_nStatus = m_nPreStatus;
    /* Seek completed, notify user layer AIP */
    EC_VOIDP pUserData = m_sMediaNotify.pUserData;
    MediaEngNotifyID nID = MediaEngNotify_SeekCompleted;
    m_sMediaNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID Framework::DoStop()
{
    /* Stop all modules */
    if (m_pAudioRender) m_pAudioRender->Stop();
    if (m_pVideoRender) m_pVideoRender->Stop();
    if (m_pMediaClock) m_pMediaClock->Stop();
    if (m_pAudioDecoder) m_pAudioDecoder->Stop();
    if (m_pVideoDecoder) m_pVideoDecoder->Stop();
    if (m_pSource) m_pSource->Stop();
    /* Wait stoped finished */
    m_semMediaEngStoped.WaitSIGNAL();

    /* clear all resource */
    Reset();
    
    m_pThread->ClearMsg();
    m_nStatus = MediaEngStatus_Stop;
    /* MediaEngine Stoped, notify user layer AIP */
    EC_VOIDP pUserData = m_sMediaNotify.pUserData;
    MediaEngNotifyID nID = MediaEngNotify_MediaStoped;
    m_sMediaNotify.NotifyHandler(pUserData, nID, EC_NULL, EC_NULL);
}

EC_VOID Framework::DispatchMsg(void* pMsg)
{
    if (EC_NULL == pMsg) return;

    MediaEngMsg *pMediaMsg = (MediaEngMsg*)pMsg;
    switch (pMediaMsg->nCmd)
    {
        case MediaEngCommand_Play:
        {
            DoPlay();
        }
        break;

        case MediaEngCommand_Pause:
        {
            DoPause();
        }
        break;

        case MediaEngCommand_Seek:
        {
            EC_U32 *pSeekPos = (EC_U32*)pMediaMsg->pParam;
            DoSeek(*pSeekPos);
        }
        break;

        case MediaEngCommand_Stop:
        {
            DoStop();
        }
        break;

        default: break;
    }
}

EC_BOOL Framework::CheckStatusCanSwitch(MediaEngStatus nCurStatus,
                                        MediaEngStatus nNewStatus)
{
    /* same status no need switch */
    if(nCurStatus == nNewStatus) return EC_FALSE;
    /* when doing switching or seeking */
    if((MediaEngStatus_Seeking == nCurStatus) ||
       (MediaEngStatus_Switching == nCurStatus)) return EC_FALSE;
    /* when engine stoped, pause/seek forbid */
    if(((MediaEngStatus_Pause == nNewStatus)    ||
        (MediaEngStatus_Playing == nNewStatus)  ||
        (MediaEngStatus_Seeking == nNewStatus)) &&
        (MediaEngStatus_Stop == nCurStatus) ) return EC_FALSE;
    /* media opend, just go to playing status */
    if((MediaEngStatus_MediaOpend == nCurStatus) &&
       (MediaEngStatus_Playing != nNewStatus)) return EC_FALSE;
    /* media engine inited, open a media is only feasible */
    if((MediaEngStatus_Inited == nCurStatus) &&
       (MediaEngStatus_MediaOpend != nNewStatus)) return EC_FALSE;

    return  EC_TRUE;
}

EC_S32 Framework::NotifyHandler(EC_VOIDP pUserData, EC_S32 nID,
                                EC_VOIDP pParam1, EC_VOIDP pParam2)
{
    Framework *pEng = (Framework*)pUserData;
    switch (nID)
    {
        case MediaEngNotify_PlayStarted:
        {
            break;
        }
        case MediaEngNotify_MediaPaused:
        {
            break;
        }
        case MediaEngNotify_EngSrcStoped:
        case MediaEngNotify_EngADecStoped:
        case MediaEngNotify_EngVDecStoped:
        case MediaEngNotify_EngARndStoped:
        case MediaEngNotify_EngVRndStoped:
        {
            static EC_U32 nCheckStop = 0;
            if (nCheckStop == 0)
            {
                nCheckStop |= MediaEngNotify_EngSrcStoped;
                if (pEng->m_bHasAudio)
                {
                    nCheckStop |= MediaEngNotify_EngADecStoped;
                    nCheckStop |= MediaEngNotify_EngARndStoped;
                }
                if (pEng->m_bHasVideo)
                {
                    nCheckStop |= MediaEngNotify_EngVDecStoped;
                    nCheckStop |= MediaEngNotify_EngVRndStoped;
                }
            }

            static EC_U32 nEngCurrStoped = 0;
            nEngCurrStoped = nEngCurrStoped | nID;
            if (nCheckStop == nEngCurrStoped)
            {
                nCheckStop = 0;
                nEngCurrStoped = 0;
                pEng->m_semMediaEngStoped.SendSIGNAL();
            }
            break;
        }
        case MediaEngNotify_SrcFlushCompleted:
        case MediaEngNotify_ADecFlushCompleted:
        case MediaEngNotify_VDecFlushCompleted:
        case MediaEngNotify_ARndFlushCompleted:
        case MediaEngNotify_VRndFlushCompleted:
        {
            static EC_U32 nCheckFlush = 0;
            if (nCheckFlush == 0)
            {
                nCheckFlush |= MediaEngNotify_SrcFlushCompleted;
                if (pEng->m_bHasAudio)
                    nCheckFlush |= MediaEngNotify_ADecFlushCompleted;
                if (pEng->m_bHasVideo)
                    nCheckFlush |= MediaEngNotify_VDecFlushCompleted;
            }

            static EC_U32 nFlushComplete = 0;
            nFlushComplete = nFlushComplete | nID;
            if (nCheckFlush == nFlushComplete)
            {
                nCheckFlush = 0;
                nFlushComplete = 0;
                pEng->m_nSeekPos = -1;
                pEng->m_semFlushCompleted.SendSIGNAL();
            }
            break;
        }
        case MediaEngNotify_EngARndPlayFinished:
        case MediaEngNotify_EngVRndPlayFinished:
        {

            static EC_U32 nCheckFinished = 0;
            if (nCheckFinished == 0)
            {
                if (pEng->m_bHasAudio)
                    nCheckFinished |= MediaEngNotify_EngARndPlayFinished;
                if (pEng->m_bHasVideo)
                    nCheckFinished |= MediaEngNotify_EngVRndPlayFinished;
            }

            static EC_U32 nFinishRecv = 0;
            nFinishRecv = nFinishRecv | nID;
            if (nCheckFinished == nFinishRecv)
            {
                //pEng->Stop();
                EC_U32 ID = MediaEngNotify_PlaybackFinished;
                EC_VOIDP pUserData = pEng->m_sMediaNotify.pUserData;
                pEng->m_sMediaNotify.NotifyHandler(pUserData, ID, EC_NULL, EC_NULL);
            }
            break;
        }
        default: break;
    }
    return 0;
}
