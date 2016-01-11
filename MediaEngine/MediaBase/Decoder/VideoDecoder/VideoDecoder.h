/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoDecoder.h
 * This file for Media video decoder module class define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_DECODER_H
#define VIDEO_DECODER_H

#include "ECType.h"
#include "Source.h"
#include "ECThread.h"
#include "FFmpegVideoDec.h"
#include "SourcePort.h"
#include "MediaMsgHandler.h"
#include "VideoFrameManager.h"

class VideoDecPort;
class VideoDecoder : public MediaMsgHandler
{
public:
    VideoDecoder();
    ~VideoDecoder();
    EC_U32 Init(MediaCtxInfo* pMediaInfo,
                SourcePort* pSourcePort,
                MediaEngNotify* pNotify);
    EC_VOID Uninit();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    EC_VOID Flush();
    VideoDecPort* GetVideoDecPort();
    EC_VOID DispatchMsg(EC_VOIDP pMsg = EC_NULL);
    EC_U32 GetVdieoFrame(VideoFrame** ppFrame);
    EC_VOID ReturnVdieoFrame(VideoFrame* pFrame);

private:
    EC_VOID DoFlush();
    EC_VOID DecodeVideo();
    EC_VOID ClearAllBuffers();
    EC_VOID HandleControlMsg(EC_VOIDP pMsg);
private:
    EC_BOOL               m_bEOS;
    VideoDecPort*         m_pPort;
    ECThread*             m_pThread;
    SourcePort*           m_pSourcePort;
    MediaEngNotify        m_sEngineNotify;
    VideoFrameManager*    m_pBufferManager;
    FFmpegVideoDec*       m_pFFmpegVideoDec;
};

#endif /* VIDEO_DECODER_H */