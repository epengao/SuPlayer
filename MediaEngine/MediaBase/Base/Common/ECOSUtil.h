/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECOSUtil.h
 * This program is file for OS depends Util functions.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_OS_UTIL_H
#define EC_OS_UTIL_H

#include "ECType.h"

#ifdef __cplusplus
extern "C" {
#endif


EC_U32  ecGetSystemTime();
EC_U64  ecGetSystemTimeU();
EC_U32  ecGetRandNumber();
EC_VOID ecSleep(EC_U32 nTime);
EC_VOID ecUSleep(EC_U32 nTime);
EC_VOID ecGetSystemDate(EC_Date *pDate);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* EC_OS_UTIL_H */