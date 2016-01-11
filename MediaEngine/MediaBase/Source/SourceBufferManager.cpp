/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* SourceBufferManager.cpp
* This file for Media Source Buffer Manager implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECAutoLock.h"
#include "SourceBufferManager.h"


SourceBufferManager::SourceBufferManager(EC_U32 nBufferQueueMaxSize)
{
    m_pVideoBufQueue = new ECRingQueue<SourceBuffer*>(nBufferQueueMaxSize);
    m_pAudioBufQueue = new ECRingQueue<SourceBuffer*>(nBufferQueueMaxSize);
    m_pReuseAVBufQueue = new ECRingQueue<SourceBuffer*>(nBufferQueueMaxSize*2);
}

SourceBufferManager::~SourceBufferManager()
{
    if (m_pVideoBufQueue) delete m_pVideoBufQueue;
    if (m_pAudioBufQueue) delete m_pAudioBufQueue;
    if (m_pReuseAVBufQueue) delete m_pReuseAVBufQueue;
}

EC_BOOL SourceBufferManager::IsVideoBufferQueueFull()
{
    ECAutoLock Lock(&m_mtxVideoBuf);
    return m_pVideoBufQueue->IsFull();
}

EC_BOOL SourceBufferManager::IsAudioBufferQueueFull()
{
    ECAutoLock Lock(&m_mtxAudioBuf);
    return m_pAudioBufQueue->IsFull();
}

/* Video Buffer Property*/
EC_U32 SourceBufferManager::PushVideoBuffer(SourceBuffer *pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxVideoBuf);
        return m_pVideoBufQueue->Push(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PopVideoBuffer(SourceBuffer **pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxVideoBuf);
        return m_pVideoBufQueue->Pop(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PushReuseVideoBuffer(SourceBuffer *pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAVReuseBuf);
        return m_pReuseAVBufQueue->Push(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PopReuseVideoBuffer(SourceBuffer **pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAVReuseBuf);
        return m_pReuseAVBufQueue->Pop(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

/* Audio Buffer Property*/
EC_U32 SourceBufferManager::PushAudioBuffer(SourceBuffer *pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAudioBuf);
        return m_pAudioBufQueue->Push(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PopAudioBuffer(SourceBuffer **pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAudioBuf);
        return m_pAudioBufQueue->Pop(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PushReuseAudioBuffer(SourceBuffer *pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAVReuseBuf);
        return m_pReuseAVBufQueue->Push(pBuffer);
    }
    else
        return EC_Err_BadParam;
}

EC_U32 SourceBufferManager::PopReuseAudioBuffer(SourceBuffer **pBuffer)
{
    if (pBuffer)
    {
        ECAutoLock Lock(&m_mtxAVReuseBuf);
        return m_pReuseAVBufQueue->Pop(pBuffer);
    }
    else
        return EC_Err_BadParam;
}
