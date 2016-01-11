/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
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