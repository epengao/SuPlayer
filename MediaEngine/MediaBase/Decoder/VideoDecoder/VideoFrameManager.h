/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoFrameManager.h
 * This file defines the Video Frame Manager, manager all the YUV Frame
 * buffers, for decoder module output here and draw frames to screen.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_FRAME_MANAGER_H
#define VIDEO_FRAME_MANAGER_H

#include "ECType.h"
#include "ECMutex.h"
#include "VideoDec.h"
#include "ECRingQueue.h"


#define VIDEO_RENDER_BUFFER_QUEUE_MAX_SIZE 2

class VideoFrameManager
{
public:
    VideoFrameManager(EC_U32 nBufferQueueMaxSize = VIDEO_RENDER_BUFFER_QUEUE_MAX_SIZE);
    ~VideoFrameManager();
    EC_BOOL IsVideoFrameQueueFull();
    EC_U32 PushVideoFrame(VideoFrame *pFrame);
    EC_U32 PopVideoFrame(VideoFrame **ppFrame);
    EC_U32 PushReuseVideoFrame(VideoFrame *pFrame);
    EC_U32 PopReuseVideoFrame(VideoFrame **ppFrame);

private:
    ECMutex                     m_mtxVideoFrame;
    ECRingQueue<VideoFrame*>*   m_pVideoFrameQueue;
    ECMutex                     m_mtxReuseVideoFrame;
    ECRingQueue<VideoFrame*>*   m_pReuseVideoFrameQueue;
};

#endif /* VIDEO_FRAME_MANAGER_H */