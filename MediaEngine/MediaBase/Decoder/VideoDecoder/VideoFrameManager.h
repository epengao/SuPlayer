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