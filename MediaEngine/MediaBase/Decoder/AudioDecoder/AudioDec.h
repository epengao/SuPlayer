/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ... 
* 
* Project:  Enjoyable Coding < EC >
* 
* AudioDec.h
* This file for define the Audio Decoder Error Code.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef AUDIO_DEC_H
#define AUDIO_DEC_H

#include "ECType.h"
#include "ECError.h"

#ifdef __cplusplus
extern "C" {
#endif


#define    Audio_Dec_Err_None                  0x00000000
#define    Audio_Dec_Err_NoDecoder             0x0000A001
#define    Audio_Dec_Err_OpenDecoderFaild      0x0000A002
#define    Audio_Dec_Err_DecDataFaild          0x0000A003
#define    Audio_Dec_Err_NeedRetry             0x0000A004
#define    Audio_Dec_Err_EndOfPlayback         0x0000A005

/* Audio PCM Buffer */
#define AudioPCMBuffer void

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AUDIO_DEC_H */
