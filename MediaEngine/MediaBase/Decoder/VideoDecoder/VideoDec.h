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
* VideoDec.h
* This file for define the Video Decoder Error Code.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef VIDEO_DEC_H
#define VIDEO_DEC_H

#include "ECType.h"
#include "ECError.h"

#ifdef __cplusplus
extern "C" {
#endif


#define    Video_Dec_Err_None                  0x00000000
#define    Video_Dec_Err_NoDecoder             0x0000B001
#define    Video_Dec_Err_OpenDecoderFaild      0x0000B002
#define    Video_Dec_Err_DecDataFaild          0x0000B003
#define    Video_Dec_Err_NeedRetry             0x0000B004
#define    Video_Dec_Err_EndOfPlayback         0x0000B005

/* VideoFrame */
#define VideoFrame void

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VIDEO_DEC_H */
