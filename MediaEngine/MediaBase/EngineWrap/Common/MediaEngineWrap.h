/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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
