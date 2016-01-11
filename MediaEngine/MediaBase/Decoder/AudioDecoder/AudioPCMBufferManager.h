/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * AudioPCMBufferManager.h
 * This file defines the Audio PCM Buffer Manager, manager all the Audio PCM
 * buffers, for decoder module output here and send the PCM data to Audio Card.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef AUDIO_PCM_BUFFER_MANAGER_H
#define AUDIO_PCM_BUFFER_MANAGER_H

#include "ECType.h"
#include "AudioDec.h"
#include "ECMutex.h"
#include "ECRingQueue.h"


#define AUDIO_PCM_BUFFER_QUEUE_MAX_SIZE 4

class AudioPCMBufferManager
{
public:
    AudioPCMBufferManager(EC_U32 nBufferQueueMaxSize = AUDIO_PCM_BUFFER_QUEUE_MAX_SIZE);
    ~AudioPCMBufferManager();
    EC_BOOL IsAudioPCMBufferQueueFull();
    EC_U32 PushAudioPCMBuffer(AudioPCMBuffer *pBuffer);
    EC_U32 PopAudioPCMBuffer(AudioPCMBuffer **ppBuffer);
    EC_U32 PushReuseAudioPCMBuffer(AudioPCMBuffer *pBuffer);
    EC_U32 PopReuseAudioPCMBuffer(AudioPCMBuffer **ppBuffer);

private:
    ECMutex                       m_mtxAudioPCMBuf;
    ECRingQueue<AudioPCMBuffer*>* m_pAudioPCMBufQueue;
    ECMutex                       m_mtxReuseAudioPCMBuf;
    ECRingQueue<AudioPCMBuffer*>* m_pReuseAudioPCMBufQueue;
};

#endif /* AUDIO_PCM_BUFFER_MANAGER_H */