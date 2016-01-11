/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoDecPort.h
 * This file define a Port, for other moduels get uncompressed data,
 * [AudioPCM].
 * We can add other methods to this class to extend the Port.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_DEC_PORT_H
#define VIDEO_DEC_PORT_H


#include "ECType.h"
#include "VideoDec.h"
#include "VideoDecoder.h"

class VideoDecPort
{
public:
    VideoDecPort(VideoDecoder* pOwner);
    ~VideoDecPort();
    EC_U32 GetVideoFrame(VideoFrame** ppFrame);
    EC_VOID ReturnVideoFrame(VideoFrame* pFrame);

private:
    VideoDecoder*    m_pOwner;
};

#endif /* VIDEO_DEC_PORT_H */