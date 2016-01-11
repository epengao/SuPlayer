/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ecMemOP.cpp
 * This file for all EC memory operation interface implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include "ECMemOP.h"


EC_PTR ecMemAlloc(EC_U32 uSize)
{
    return malloc(uSize);
}

EC_VOID ecMemFree(EC_PTR pMem)
{
    free(pMem);
}

EC_VOID ecMemSet(EC_PTR pMem, EC_S32 val, EC_U32 uSize)
{
    memset(pMem, val, uSize);
}

EC_VOID ecMemCopy(EC_PTR pDest, EC_PTR pSrc, EC_U32 uSize)
{
    memcpy(pDest, pSrc, uSize);
}

EC_S32 ecMemCompare(EC_PTR pBuf1, EC_PTR pBuf2, EC_U32 uSize)
{
    return memcmp(pBuf1, pBuf2, uSize);
}

EC_VOID ecMemMove(EC_PTR pDest, EC_PTR pSrc, EC_U32 uSize)
{
    memmove (pDest, pSrc, uSize);
}
