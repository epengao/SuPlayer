/*
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
* Copyright (C) 2014-2016 Gao Peng

* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.

* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.

* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the Free
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

* ---------------------------------------------------------------------
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