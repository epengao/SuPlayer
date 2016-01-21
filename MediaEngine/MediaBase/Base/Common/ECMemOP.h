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
* ECMemOP.h
* This file for all EC memory operation interface define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECType.h"

#ifdef __cplusplus
extern "C" {
#endif

EC_PTR ecMemAlloc(EC_U32 uSize);
EC_VOID ecMemFree(EC_PTR pMem);
EC_VOID ecMemSet(EC_PTR pMem, EC_S32 val, EC_U32 uSize);
EC_VOID ecMemCopy(EC_PTR pDest, EC_PTR pSrc, EC_U32 uSize);
EC_VOID ecMemMove(EC_PTR pDest, EC_PTR pSrc, EC_U32 uSize);
EC_S32 ecMemCompare(EC_PTR pBuf1, EC_PTR pBuf2, EC_U32 uSize);

#ifdef __cplusplus
}
#endif