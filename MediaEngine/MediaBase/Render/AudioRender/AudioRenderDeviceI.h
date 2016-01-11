/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * AudioRenderDeviceI.h
 * Here we define a Interface for defferent Platform following.
 * Different platform need implement individual audio render device.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef AUDIO_RENDER_DEVICE_I_H
#define AUDIO_RENDER_DEVICE_I_H

#include "ECType.h"
#include "Source.h"
#include "AudioRend.h"
#include "MediaCommon.h"

class AudioRenderDeviceI
{
public:
    virtual ~AudioRenderDeviceI(){};
    virtual EC_U32 Init(MediaCtxInfo* pMediaInfo,
                        AudioPCMBuffer *pFirstFrame) = 0;
    virtual EC_VOID Uninit() = 0;
    virtual EC_VOID Run() = 0;
    virtual EC_VOID Pause() = 0;
    virtual EC_VOID Stop() = 0;
    virtual EC_VOID Flush() = 0;
    virtual EC_VOID SendPCMData(AudioPCMBuffer *pBuffer, EC_U32 nSize) = 0;
};

#endif /* AUDIO_RENDER_DEVICE_I_H */