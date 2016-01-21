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