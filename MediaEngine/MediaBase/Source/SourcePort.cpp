/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* SourcePort.cpp
* This file for Source Port class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "SourcePort.h"

SourcePort::SourcePort(MediaSource* pOwner)
:m_pOwner(pOwner)
{
}

SourcePort::~SourcePort()
{
}

EC_U32 SourcePort::GetVideoBuffer(SourceBuffer** ppBuffer)
{
    return m_pOwner->GetVdieoBuffer(ppBuffer);
}

EC_VOID SourcePort::ReturnVideoBuffer(SourceBuffer* pBuffer)
{
    m_pOwner->ReturnVideoBuffer(pBuffer);
}

EC_U32 SourcePort::GetAudioBuffer(SourceBuffer** ppBuffer)
{
    return m_pOwner->GetAudioBuffer(ppBuffer);
}

EC_VOID SourcePort::ReturnAudioBuffer(SourceBuffer* pBuffer)
{
    m_pOwner->ReturnAudioBuffer(pBuffer);
}
