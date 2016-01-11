/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
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
