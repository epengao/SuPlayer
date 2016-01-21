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
* AudioRend.h
*
* This file Defines the Audio Render Errors.
* All about the Audio render header define will be here.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef AUDIO_REND_H
#define AUDIO_REND_H

#include "ECType.h"
#include "ECError.h"
#include "AudioDec.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Video Render Error */
#define    Audio_Render_Err_None                   0x00000000
#define    Audio_Render_Err_InitFail               0x00A00001
#define    Audio_Render_Err_CreatWaveScaleFail     0x00A00002

typedef void (*playSoundCallback)(EC_VOIDP pUserData, EC_U8 *pStream, EC_S32 nLen);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AUDIO_REND_H */