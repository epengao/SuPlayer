/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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