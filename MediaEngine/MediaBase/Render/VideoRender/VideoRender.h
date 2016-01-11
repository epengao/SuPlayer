/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoRender.h
 * This file for Media Video Render class APIs define. Framework will send
 * all the video frames to here, and render the video frame pictures to the
 * scream.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_RENDER_H
#define VIDEO_RENDER_H

#include "ECType.h"
#include "Source.h"
#include "ECThread.h"
#include "VideoRend.h"
#include "FrameScale.h"
#include "ClockPort.h"
#include "VideoDecPort.h"
#include "MediaMsgHandler.h"
#include "VideoRenderDeviceI.h"

/* Here we use milisecond timestamp */
#define    MAX_VIDEO_FRAME_DELAY    100

class VideoRender : public MediaMsgHandler
{
public:
    VideoRender();
    ~VideoRender();
public:
    EC_U32 Init(MediaCtxInfo *pMediaInfo,
                VideoDecPort* pVideoDecPort,
                ClockPort* pClockPort, 
                EC_VOIDP pVideoScreen,
                MediaEngNotify *pNotify);
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Seek(EC_U32 nPos);
    EC_VOID Stop();
    EC_VOID Flush();
    EC_VOID Uninit();
    EC_VOID DispatchMsg(EC_VOIDP pMsg = EC_NULL);
    EC_VOID UpdateVideoScreen(EC_VOIDP pVideoScreen);

private:
    EC_VOID DoFlush();
    EC_VOID RenderVideo();
    EC_VOID HandleControlMsg(EC_VOIDP pMsg);
    TimeStamp SyncClockTime(TimeStamp nTime);
private:
    EC_U32               m_nVideoWidth;
    EC_U32               m_nVideoHeight;
    EC_U32               m_nScreenWidth;
    EC_U32               m_nScreenHeight;
    ECThread*            m_pThread;
    MediaCtxInfo*        m_pMediaInfo;
    FrameScale*          m_pFrameScale;
    ClockPort*           m_pClockPort;
    VideoDecPort*        m_pVideoDecPort;
    MediaEngNotify       m_sEngineNotify;
    MediaEngStatus       m_nStatus;
    ECMutex              m_mtxRender;
    EC_BOOL              m_bNeedRender;
    VideoFrame*          m_pLatestRenderFrame;
    VideoRenderDeviceI*  m_pVideoRndDevice;
};

#endif /* VIDEO_RENDER_H */