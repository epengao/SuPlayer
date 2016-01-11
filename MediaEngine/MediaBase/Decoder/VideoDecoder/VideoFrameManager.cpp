/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* VideoFrameManager.cpp
* This file is the class VideoFrameManager implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECAutoLock.h"
#include "VideoFrameManager.h"
extern "C"
{
#include "libavcodec/avcodec.h"
};

VideoFrameManager::VideoFrameManager(EC_U32 nBufferQueueMaxSize)
{
    m_pVideoFrameQueue = new ECRingQueue<VideoFrame*>(nBufferQueueMaxSize);
    m_pReuseVideoFrameQueue = new ECRingQueue<VideoFrame*>(nBufferQueueMaxSize*2);
}

VideoFrameManager::~VideoFrameManager()
{
    if (m_pVideoFrameQueue) delete m_pVideoFrameQueue;
    if (m_pReuseVideoFrameQueue) delete m_pReuseVideoFrameQueue;
}

EC_BOOL VideoFrameManager::IsVideoFrameQueueFull()
{
    ECAutoLock Lock(&m_mtxVideoFrame);
    return m_pVideoFrameQueue->IsFull();
}

EC_U32 VideoFrameManager::PushVideoFrame(VideoFrame *pFrame)
{
    if (EC_NULL != pFrame) 
    {
        ECAutoLock Lock(&m_mtxVideoFrame);
        return m_pVideoFrameQueue->Push(pFrame);
    }
    return EC_Err_BadParam;
}

EC_U32 VideoFrameManager::PopVideoFrame(VideoFrame **ppFrame)
{
    if (EC_NULL != ppFrame)
    {
        ECAutoLock Lock(&m_mtxVideoFrame);
        return m_pVideoFrameQueue->Pop(ppFrame);
    }
    return EC_Err_BadParam;
}

EC_U32 VideoFrameManager::PushReuseVideoFrame(VideoFrame *pFrame)
{
    if (EC_NULL != pFrame)
    {
        ECAutoLock Lock(&m_mtxReuseVideoFrame);
        return m_pReuseVideoFrameQueue->Push(pFrame);
    }
    return EC_Err_BadParam;
}

EC_U32 VideoFrameManager::PopReuseVideoFrame(VideoFrame **ppFrame)
{
    if (EC_NULL != ppFrame)
    {
        ECAutoLock Lock(&m_mtxReuseVideoFrame);
        return m_pReuseVideoFrameQueue->Pop(ppFrame);
    }
    return EC_Err_BadParam;
}
