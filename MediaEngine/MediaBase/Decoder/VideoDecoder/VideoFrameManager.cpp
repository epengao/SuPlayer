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
