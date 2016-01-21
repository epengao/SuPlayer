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
* ECStringOP.cpp
* This file for redefing all the EC string interface operation implement.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* ------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "ECStringOP.h"


EC_U32 ECStringOP::StrLen(EC_CONST_PCHAR pStr)
{
    return (EC_U32)strlen(pStr);
}

EC_CHAR ECStringOP::ToUpper(EC_CHAR cChar)
{
    EC_CHAR cRet = cChar;
    if(('a'<=cChar) && (cChar<='z'))
        cRet = (cChar-32);
    return cRet;
}

EC_CHAR ECStringOP::ToLower(EC_CHAR cChar)
{
    EC_CHAR cRet = cChar;
    if(('A'<=cChar) && (cChar<='Z'))
        cRet = (cChar+32);
    return cRet;
}

EC_PCHAR ECStringOP::ToUpperStr(EC_PCHAR pStr)
{
    EC_PCHAR pRet = pStr;
    while((*pStr) != '\0')
    {
        *pStr = ECStringOP::ToUpper(*pStr);
        pStr++;
    }
    return pRet;
}

EC_PCHAR ECStringOP::ToLowerStr(EC_PCHAR pStr)
{
    EC_PCHAR pRet = pStr;
    while((*pStr) != '\0')
    {
        *pStr = ECStringOP::ToLower(*pStr);
        pStr++;
    }
    return pRet;
}

EC_PCHAR ECStringOP::StrCopy(EC_PCHAR pDest, EC_CONST_PCHAR pSrc)
{
    return strcpy(pDest, pSrc);
}

EC_PCHAR ECStringOP::StrNCopy(EC_PCHAR pDest, const EC_PCHAR pSrc, EC_U32 uSize)
{
    return strncpy(pDest, pSrc, uSize);
}

EC_PCHAR ECStringOP::StrCat(EC_PCHAR pDest, const EC_PCHAR pSrc)
{
    return strcat(pDest, pSrc);
}

EC_PCHAR ECStringOP::StrAddPrefix(EC_PCHAR pStr, const EC_PCHAR pPrefix)
{
    EC_PCHAR pNewStr = new EC_CHAR[ECStringOP::StrLen(pStr) +
                                   ECStringOP::StrLen(pPrefix) + 1];
    ECStringOP::StrCopy(pNewStr, pPrefix);
    ECStringOP::StrCat(pNewStr, pStr);
    delete []pStr;
    pStr = pNewStr;
    return pStr;
}

EC_PCHAR ECStringOP::StrInsertChar(EC_PCHAR pStr, EC_CHAR cChar, EC_U32 uIndex)
{
    EC_U32 uLength = ECStringOP::StrLen(pStr);
    if(uIndex > uLength)
        return EC_NULL;

    EC_PCHAR pNewStr = new EC_CHAR[uLength + 2];
    if((0 < uIndex) && (uIndex < uLength))
    {
        pNewStr[uIndex] = cChar;
        ECStringOP::StrNCopy(pNewStr, pStr, uIndex);
        ECStringOP::StrCopy(pNewStr+uIndex+1, pStr+uIndex);
    }
    else if (uLength == uIndex)
    {
        ECStringOP::StrCopy(pNewStr, pStr);
        pNewStr[uLength] = cChar;
        pNewStr[uLength+1] = '\0';
    }
    else if(0 == uIndex)
    {
        pNewStr[0] = cChar;
        ECStringOP::StrCopy(pNewStr+1, pStr);
    }

    delete pStr;
    pStr = pNewStr;
    return pStr;
}

EC_PCHAR ECStringOP::StrInsertStr(EC_PCHAR pStr, const EC_PCHAR pInsert, EC_U32 uIndex)
{
    EC_U32 uSrcLength = ECStringOP::StrLen(pStr);
    EC_U32 uInsertLength = ECStringOP::StrLen(pInsert);
    EC_U32 uTotalLength = uSrcLength + uInsertLength;

    if(uIndex > uSrcLength)
        return EC_NULL;
    
    EC_PCHAR pNewStr = new EC_CHAR[uTotalLength + 1];
    if((0 < uIndex) && (uIndex < uSrcLength))
    {
        ECStringOP::StrCopy(pNewStr+uIndex, pInsert);
        ECStringOP::StrNCopy(pNewStr, pStr, uSrcLength);
        ECStringOP::StrCopy(pNewStr+uInsertLength, pStr+uIndex);
    }
    else if (uSrcLength == uIndex)
    {
        ECStringOP::StrCat(pNewStr, pInsert);
    }
    else if(0 == uIndex)
    {
        ECStringOP::StrCopy(pNewStr, pInsert);
        ECStringOP::StrCopy(pNewStr+uInsertLength, pStr);
    }
    
    delete pStr;
    pStr = pNewStr;
    return pStr;
}

EC_PCHAR ECStringOP::StrStr(EC_PCHAR pDest, EC_PCHAR pFind)
{
    return strstr(pDest, pFind);
}

EC_PCHAR ECStringOP::StrSet(EC_PCHAR pStr, EC_CHAR cChar)
{
    memset(pStr, cChar, ECStringOP::StrLen(pStr));
    return pStr;
}

EC_S32 ECStringOP::StrCompare(EC_PCHAR pStr1, EC_PCHAR pStr2)
{
    return strcmp(pStr1, pStr2);
}

EC_S32 ECStringOP::StrNCompare(EC_PCHAR pStr1, EC_PCHAR pStr2, EC_U32 uSize)
{
    return strncmp(pStr1, pStr2, uSize);
}

EC_S32 ECStringOP::StrCaseCompare(EC_PCHAR pStr1, EC_PCHAR pStr2)
{
    EC_S32 nRet;
    EC_PCHAR pTmpStr1 = new EC_CHAR[ECStringOP::StrLen(pStr1)+1];
    EC_PCHAR pTmpStr2 = new EC_CHAR[ECStringOP::StrLen(pStr2)+1];
    ECStringOP::StrCopy(pTmpStr1, pStr1);
    ECStringOP::StrCopy(pTmpStr2, pStr2);
    nRet = ECStringOP::StrCompare(ECStringOP::ToLowerStr(pTmpStr1), 
                                    ECStringOP::ToLowerStr(pTmpStr2));
    delete []pTmpStr1;
    delete []pTmpStr2;
    return nRet;
}

EC_S32 ECStringOP::StrNCaseCompare(EC_PCHAR pStr1, EC_PCHAR pStr2, EC_U32 uSize)
{
    EC_S32 nRet;
    EC_PCHAR pTmpStr1 = new EC_CHAR[ECStringOP::StrLen(pStr1)+1];
    EC_PCHAR pTmpStr2 = new EC_CHAR[ECStringOP::StrLen(pStr2)+1];
    ECStringOP::StrCopy(pTmpStr1, pStr1);
    ECStringOP::StrCopy(pTmpStr2, pStr2);
    nRet = ECStringOP::StrNCompare(ECStringOP::ToLowerStr(pTmpStr1), 
                                     ECStringOP::ToLowerStr(pTmpStr2), uSize);
    delete []pTmpStr1;
    delete []pTmpStr2;
    return nRet;
}

EC_S32 ECStringOP::StrToInt(const EC_PCHAR pStr)
{
    return atoi(pStr);
    return 0;
}

EC_PCHAR ECStringOP::IntToStr(EC_PCHAR pStr, EC_S32 nInt)
{
    sprintf(pStr, "%d", nInt);
    return pStr;
}

EC_PCHAR ECStringOP::WideStrToCStr(EC_PCHAR pStr, const EC_PWCHAR pWstr)
{
    wcstombs(pStr, pWstr, wcslen(pWstr));
    return pStr;
}

EC_PWCHAR ECStringOP::CStrToWideStr(EC_PWCHAR pWstr, const EC_PCHAR pStr)
{
    mbstowcs(pWstr, pStr, ECStringOP::StrLen(pStr));
    return pWstr;
}
