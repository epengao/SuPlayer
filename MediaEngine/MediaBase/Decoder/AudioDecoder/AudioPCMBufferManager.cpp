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
* AudioPCMBufferManager.cpp
* This file is the class AudioPCMBufferManager implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECAutoLock.h"
#include "AudioPCMBufferManager.h"
extern "C"
{
#include "libavcodec/avcodec.h"
};

AudioPCMBufferManager::AudioPCMBufferManager(EC_U32 nBufferQueueMaxSize)
{
    m_pAudioPCMBufQueue = new ECRingQueue<AudioPCMBuffer*>(nBufferQueueMaxSize);
    m_pReuseAudioPCMBufQueue = new ECRingQueue<AudioPCMBuffer*>(nBufferQueueMaxSize*2);
}

AudioPCMBufferManager::~AudioPCMBufferManager()
{
    if (m_pAudioPCMBufQueue) delete m_pAudioPCMBufQueue;
    if (m_pReuseAudioPCMBufQueue) delete m_pReuseAudioPCMBufQueue;
}

EC_BOOL AudioPCMBufferManager::IsAudioPCMBufferQueueFull()
{
    return m_pAudioPCMBufQueue->IsFull();
}

EC_U32 AudioPCMBufferManager::PushAudioPCMBuffer(AudioPCMBuffer *pBuffer)
{
    if (EC_NULL != pBuffer)
    {
        ECAutoLock Lock(&m_mtxAudioPCMBuf);
        return m_pAudioPCMBufQueue->Push(pBuffer);
    }
    return EC_Err_BadParam;
}

EC_U32 AudioPCMBufferManager::PopAudioPCMBuffer(AudioPCMBuffer **ppBuffer)
{
    if (EC_NULL != ppBuffer)
    {
        ECAutoLock Lock(&m_mtxAudioPCMBuf);
        return m_pAudioPCMBufQueue->Pop(ppBuffer);
    }
    return EC_Err_BadParam;
}

EC_U32 AudioPCMBufferManager::PushReuseAudioPCMBuffer(AudioPCMBuffer *pBuf)
{
    if (EC_NULL != pBuf)
    {
        ECAutoLock Lock(&m_mtxReuseAudioPCMBuf);
        return m_pReuseAudioPCMBufQueue->Push(pBuf);
    }
    return EC_Err_BadParam;
}

EC_U32 AudioPCMBufferManager::PopReuseAudioPCMBuffer(AudioPCMBuffer **ppBuffer)
{
    if (EC_NULL != ppBuffer) 
    {
        ECAutoLock Lock(&m_mtxReuseAudioPCMBuf);
        return m_pReuseAudioPCMBufQueue->Pop(ppBuffer);
    }
    return EC_Err_BadParam;
}
