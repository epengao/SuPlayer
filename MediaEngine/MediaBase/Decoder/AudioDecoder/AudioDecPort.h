/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * AudioDecPort.h
 * This file define a Port, for other moduels get uncompressed data,
 * [AudioPCM].
 * We can add other methods to this class to extend the Port.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef AUDIO_DEC_PORT_H
#define AUDIO_DEC_PORT_H


#include "ECType.h"
#include "AudioDec.h"
#include "AudioDecoder.h"

class AudioDecPort
{
public:
    AudioDecPort(AudioDecoder* pOwner);
    ~AudioDecPort();
    EC_U32 GetAudioPCMBuffer(AudioPCMBuffer** ppFrame);
    EC_VOID ReturnAudioPCMBuffer(AudioPCMBuffer* pFrame);

private:
    AudioDecoder*    m_pOwner;
};

#endif /* AUDIO_DEC_PORT_H */