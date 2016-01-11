/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * SourcePort.h
 * This file define a Port, for other moduels get source [video/audio/subtitle]
 * buffers. We can add other methods to this class to extend the Port.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef SOURCE_PORT_H
#define SOURCE_PORT_H


#include "ECType.h"
#include "Source.h"
#include "MediaSource.h"

class SourcePort
{
public:
    SourcePort(MediaSource* pOwner);
    ~SourcePort();
    EC_U32 GetVideoBuffer(SourceBuffer** ppBuffer);
    EC_VOID ReturnVideoBuffer(SourceBuffer* pBuffer);
    EC_U32 GetAudioBuffer(SourceBuffer** ppBuffer);
    EC_VOID ReturnAudioBuffer(SourceBuffer* pBuffer);

private:
    MediaSource*    m_pOwner;
};

#endif /* SOURCE_PORT_H */