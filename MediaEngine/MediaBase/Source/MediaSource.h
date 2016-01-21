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
* MediaSource.h
* This file for Media data source define, Framework will call this
* module to extract the medai [video/audio/subtitle] data, and then
* send these data to media decoder...
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef MEDIA_SOURCE_H
#define MEDIA_SOURCE_H

#include "ECType.h"
#include "Source.h"
#include "ECThread.h"
#include "MediaCommon.h"
#include "FFmpegReader.h"
#include "MediaMsgHandler.h"
#include "SourceBufferManager.h"

class SourcePort;
class MediaSource : public MediaMsgHandler
{
public:
    MediaSource();
    ~MediaSource();
    EC_U32 Init(EC_CONST_PCHAR pMediaPath,
                MediaEngNotify *pNotify);
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Seek(EC_U32 nPos);
    EC_VOID Stop();
    EC_VOID Flush();
    EC_VOID Uninit();
    MediaCtxInfo* GetMediaInfo();
    SourcePort* GetSourcePort();
    EC_VOID DispatchMsg(EC_VOIDP pMsg = EC_NULL);
    EC_U32 GetVdieoBuffer(SourceBuffer** ppBuffer);
    EC_U32 GetAudioBuffer(SourceBuffer** ppBuffer);
    EC_VOID ReturnVideoBuffer(SourceBuffer* pBuffer);
    EC_VOID ReturnAudioBuffer(SourceBuffer* pBuffer);

private:
    EC_VOID DoFlush();
    EC_VOID ReadSourceBuffer();
    EC_VOID HandleControlMsg(EC_VOIDP pMsg);
    EC_VOID ClearAllBuffers();
private:
    SourcePort*           m_pPort;
    ECThread*             m_pThread;
    MediaCtxInfo*         m_pMediaInfo;
    MediaEngNotify        m_sEngineNotify;
    EC_BOOL               m_bEndOfSource;
    FFmpegReader*         m_pFFmpegReader;
    SourceBufferManager*  m_pBufferManager;
};

#endif /* MEDIA_SOURCE_H */