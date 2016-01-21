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