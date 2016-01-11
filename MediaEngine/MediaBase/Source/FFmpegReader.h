/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * FFmpegReader.h
 * This file for Media FFmpeg Source data reader Class define. This class 
 * read the data from media[local file/ remote URL], read video/adio/subtitle
 * data, then send the data buffer to SourceBufferManager.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef MEDIA_SOURCE_READER_H
#define MEDIA_SOURCE_READER_H

#include "ECType.h"
#include "Source.h"
#include "ECString.h"

extern "C"
{
#include "libavformat/avformat.h"
};

class FFmpegReader
{
public:
    FFmpegReader(EC_CONST_PCHAR pMediaPath);
    ~FFmpegReader();
public:
    EC_U32 Init();
    EC_U32 Seek(EC_U32 nPos);
    EC_U32 ReadSourceBuffer(EC_VOIDP* ppBuffer);
    EC_VOID ReleaseSourceBuffer(EC_VOIDP pBuffer);
    EC_VOID Uninit();
    EC_U32 GetMediaInfo(MediaCtxInfo **ppMediaInfo);

private:
    EC_S32 m_nVideoIndex;
    EC_S32 m_nAudioIndex;
    ECString m_strMediaPath;
    AVFormatContext	*m_pFormatCtx;
};

#endif /* MEDIA_SOURCE_READER_H */