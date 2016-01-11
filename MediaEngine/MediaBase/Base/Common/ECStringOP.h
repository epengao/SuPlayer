/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Project:  Enjoyable Coding< EC >
 *
 * ECStringOP.h
 * This file for redefing all EC string operation interface define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */


#include <string.h>
#include "ECType.h"


class ECStringOP
{
public:
    static EC_U32 StrLen(EC_CONST_PCHAR pStr);
    static EC_CHAR ToUpper(EC_CHAR cChar);
    static EC_CHAR ToLower(EC_CHAR cChar);
    static EC_PCHAR ToUpperStr(EC_PCHAR pStr);
    static EC_PCHAR ToLowerStr(EC_PCHAR pStr);
    static EC_PCHAR StrCopy(EC_PCHAR pDest, EC_CONST_PCHAR pSrc);
    static EC_PCHAR StrNCopy(EC_PCHAR pDest, const EC_PCHAR pSrc, EC_U32 uSize);
    static EC_PCHAR StrCat(EC_PCHAR pDest, const EC_PCHAR pSrc);
    static EC_PCHAR StrAddPrefix(EC_PCHAR pStr, const EC_PCHAR pPrefix);
    static EC_PCHAR StrInsertChar(EC_PCHAR pStr, EC_CHAR cChar, EC_U32 uIndex);
    static EC_PCHAR StrInsertStr(EC_PCHAR pStr, const EC_PCHAR pInsert, EC_U32 uIndex);
    static EC_PCHAR StrStr(EC_PCHAR pDest, EC_PCHAR pFind);
    static EC_PCHAR StrSet(EC_PCHAR pStr, EC_CHAR cChar);
    static EC_PCHAR IntToStr(EC_PCHAR pStr, EC_S32 nInt);
    static EC_PCHAR WideStrToCStr(EC_PCHAR pStr, EC_PWCHAR pWstr);
    static EC_PWCHAR CStrToWideStr(EC_PWCHAR pWstr, EC_PCHAR pStr);
    static EC_S32 StrToInt(const EC_PCHAR pStr);
    static EC_S32 StrCompare(EC_PCHAR pStr1, EC_PCHAR pStr2);
    static EC_S32 StrNCompare(EC_PCHAR pStr1, EC_PCHAR pStr2, EC_U32 uSize);
    static EC_S32 StrCaseCompare(EC_PCHAR pStr1, EC_PCHAR pStr2);
    static EC_S32 StrNCaseCompare(EC_PCHAR pStr1, EC_PCHAR pStr2, EC_U32 uSize);

private:
    ECStringOP();
};

