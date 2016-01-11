/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* AudioDecPort.cpp
* This file for VideoDecPort class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "AudioDecPort.h"

AudioDecPort::AudioDecPort(AudioDecoder* pOwner)
:m_pOwner(pOwner)
{
}

AudioDecPort::~AudioDecPort()
{
}

EC_U32 AudioDecPort::GetAudioPCMBuffer(AudioPCMBuffer** ppFrame)
{
    return m_pOwner->GetAudioPCMBuffer(ppFrame);
}

EC_VOID AudioDecPort::ReturnAudioPCMBuffer(AudioPCMBuffer* pFrame)
{
    m_pOwner->ReturnAudioPCMBuffer(pFrame);
}
