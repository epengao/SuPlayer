/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* VideoDecPort.cpp
* This file for VideoDecPort class implemetaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "VideoDecPort.h"

VideoDecPort::VideoDecPort(VideoDecoder* pOwner)
:m_pOwner(pOwner)
{
}

VideoDecPort::~VideoDecPort()
{
}

EC_U32 VideoDecPort::GetVideoFrame(VideoFrame** ppFrame)
{
    return m_pOwner->GetVdieoFrame(ppFrame);
}

EC_VOID VideoDecPort::ReturnVideoFrame(VideoFrame* pFrame)
{
    m_pOwner->ReturnVdieoFrame(pFrame);
}
