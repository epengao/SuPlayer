/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * VideoRend.h
 *
 * This file Defines the Video Render Errors.
 * All about the render header define will be here.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef VIDEO_REND_H
#define VIDEO_REND_H

#include "ECType.h"
#include "ECError.h"
#include "VideoDec.h"
#include "MediaCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Video Render Error */
#define    Video_Render_Err_None                   0x00000000
#define    Video_Render_Err_InitFail               0x00B00001
#define    Video_Render_Err_CreatWindowFail        0x00B00002
#define    Video_Render_Err_CreatRenderFail        0x00B00003
#define    Video_Render_Err_CreatTextureFail       0x00B00004
#define    Video_Render_Err_CreatFrameScaleFail    0x00B00005

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIDEO_REND_H */