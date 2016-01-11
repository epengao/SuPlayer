/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ... 
* 
* Project:  Enjoyable Coding < EC >
* 
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
