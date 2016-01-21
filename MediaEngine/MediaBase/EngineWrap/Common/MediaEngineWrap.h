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
* MediaEngineWrap.h
* Here we define support functions for MediaEngine wrap implement.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef MEDIA_ENGINE_WRAP_H
#define MEDIA_ENGINE_WRAP_H

#include "ECType.h"

#ifdef __cplusplus
extern "C" {
#endif

EC_S32 InitMediaEngine(MediaEngHandle *pHandle);

EC_S32 OpenMedia(MediaEngHandle handle, EC_CONST_PCHAR pMediaPath, MediaEngVideoScreen *pVideoScreen);

EC_VOID Play(MediaEngHandle handle);

EC_VOID Pause(MediaEngHandle handle);

EC_VOID Seek(MediaEngHandle handle, EC_U32 nSeekPos);

EC_VOID Stop(MediaEngHandle handle);

EC_VOID SetMediaNotify(MediaEngHandle handle, MediaEngNotify *pNotify);

EC_VOID GetMediaEngineStatus(MediaEngHandle handle, MediaEngStatus *pStatus);

EC_VOID GetMediaInfo(MediaEngHandle handle, MediaEngMediaInfo *pMediaInfo);

EC_VOID GetPlayingPosition(MediaEngHandle handle, EC_U32 *pPosition);

EC_VOID UpdateVideoScreen(MediaEngHandle handle, MediaEngVideoScreen *pVideoScreen);

EC_VOID UnInit(MediaEngHandle *pHandle);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MEDIA_ENGINE_WRAP_H */
