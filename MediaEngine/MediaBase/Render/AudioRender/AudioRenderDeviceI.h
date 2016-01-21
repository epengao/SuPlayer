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
* AudioRenderDeviceI.h
* Here we define a Interface for defferent Platform following.
* Different platform need implement individual audio render device.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef AUDIO_RENDER_DEVICE_I_H
#define AUDIO_RENDER_DEVICE_I_H

#include "ECType.h"
#include "Source.h"
#include "AudioRend.h"
#include "MediaCommon.h"

class AudioRenderDeviceI
{
public:
    virtual ~AudioRenderDeviceI(){};
    virtual EC_U32 Init(MediaCtxInfo* pMediaInfo,
                        AudioPCMBuffer *pFirstFrame) = 0;
    virtual EC_VOID Uninit() = 0;
    virtual EC_VOID Run() = 0;
    virtual EC_VOID Pause() = 0;
    virtual EC_VOID Stop() = 0;
    virtual EC_VOID Flush() = 0;
    virtual EC_VOID SendPCMData(AudioPCMBuffer *pBuffer, EC_U32 nSize) = 0;
};

#endif /* AUDIO_RENDER_DEVICE_I_H */