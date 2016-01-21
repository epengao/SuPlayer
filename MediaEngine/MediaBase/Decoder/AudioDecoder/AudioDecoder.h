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
* AudioDecoder.h
* This file for Media audio decoder module class define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

#include "ECType.h"
#include "Source.h"
#include "AudioDec.h"
#include "ECThread.h"
#include "FFmpegAudioDec.h"
#include "SourcePort.h"
#include "MediaMsgHandler.h"
#include "AudioPCMBufferManager.h"

class AudioDecPort;
class AudioDecoder : public MediaMsgHandler
{
public:
    AudioDecoder();
    ~AudioDecoder();
    EC_U32 Init(MediaCtxInfo* pMediaInfo,
                SourcePort* pSourcePort,
                MediaEngNotify *pNotify);
    EC_VOID Uninit();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    EC_VOID Flush();
    AudioDecPort* GetAudioDecPort();
    EC_VOID DispatchMsg(EC_VOIDP pMsg = EC_NULL);
    EC_U32 GetAudioPCMBuffer(AudioPCMBuffer** ppFrame);
    EC_VOID ReturnAudioPCMBuffer(AudioPCMBuffer* pFrame);

private:
    EC_VOID DoFlush();
    EC_VOID DecodeAudio();
    EC_VOID ClearAllBuffers();
    EC_VOID HandleControlMsg(EC_VOIDP pMsg);
private:
    EC_BOOL                m_bEOS;
    AudioDecPort*          m_pPort;
    ECThread*              m_pThread;
    SourcePort*            m_pSourcePort;
    MediaEngNotify         m_sEngineNotify;
    FFmpegAudioDec*        m_pFFmpegAudioDec;
    AudioPCMBufferManager* m_pBufferManager;
};

#endif /* AUDIO_DECODER_H */