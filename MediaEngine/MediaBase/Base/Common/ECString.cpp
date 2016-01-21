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
* ECString.h
* This file for EC project common string interface implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECError.h"
#include "ECString.h"
#include "ECStringOP.h"


ECString::ECString()
:m_pStr(EC_NULL)
,m_nSize(0)
{
}

ECString::~ECString()
{
    if(m_pStr)
        delete []m_pStr;
}

ECString::ECString(EC_CONST_PCHAR pStr)
:m_pStr(EC_NULL)
,m_nSize(0)
{
    if(pStr)
    {
        m_nSize = ECStringOP::StrLen(pStr);
        m_pStr = new EC_CHAR[m_nSize + 1];
        if(m_pStr)
            ECStringOP::StrCopy(m_pStr, pStr);
    }
}

ECString::ECString(const ECString &rString)
:m_pStr(EC_NULL)
{
    m_nSize = rString.m_nSize;
    if(m_nSize > 0)
    {
        m_pStr = new EC_CHAR[m_nSize + 1];
        if(m_pStr)
            ECStringOP::StrCopy(m_pStr, rString.m_pStr);
    }
}

ECString::ECString(const EC_PCHAR pStr, EC_U32 nSize)
:m_pStr(EC_NULL)
,m_nSize(nSize)
{
    m_pStr = new EC_CHAR[nSize+1];
    if(m_pStr)
    {
        m_nSize = nSize;
        ECStringOP::StrNCopy(m_pStr, pStr, nSize);
        m_pStr[m_nSize] = 0;
    }
}

ECString::ECString(const ECString &rString, EC_U32 nSize)
:m_pStr(EC_NULL)
,m_nSize(nSize)
{
    m_pStr = new EC_CHAR[nSize+1];
    if(m_pStr)
    {
        m_nSize = nSize;
        ECStringOP::StrNCopy(m_pStr, rString.ToCStr(), nSize);
        m_pStr[m_nSize] = 0;
    }
}

EC_U32 ECString::Trim()
{
    if(m_pStr)
    {
        EC_U32 nTrimN = 0;
        EC_PCHAR pTmp = EC_NULL;
        while(' ' == m_pStr[nTrimN])
            nTrimN++;
        EC_U32 nSize = m_nSize - nTrimN;
        pTmp = new EC_CHAR[nSize + 1];
        if(pTmp)
        {
            ECStringOP::StrCopy(pTmp, m_pStr+nTrimN);
            delete []m_pStr;
            m_pStr = pTmp;
            m_nSize = nSize;
        }
    }

    return EC_Err_None;
}

EC_U32 ECString::TrimEnd()
{
    if(m_pStr)
    {
        EC_U32 nTrim = 0;
        for(EC_S32 n = m_nSize-1; n >= 0; --n)
        {
            if(('\n'  != m_pStr[n]) && (' ' != m_pStr[n]))
                break;
            nTrim++;
        }

        if(nTrim > 0)
        {
            m_nSize = m_nSize - nTrim;
            m_pStr[m_nSize] = 0;
        }
    }

    return EC_Err_None;
}

EC_U32 ECString::Length() const
{
    return m_nSize;
}

EC_BOOL ECString::IsNull() const
{
    return (EC_NULL == m_pStr);
}

EC_PCHAR ECString::ToCStr() const
{
    return m_pStr;
}

EC_CHAR& ECString::operator[](EC_U32 nPos)
{
    return m_pStr[nPos];
}

EC_S32 ECString::FindChar(const EC_CHAR cChar) const
{
    EC_S32 nRet = -1;
    for(EC_U32 n = 0; n < m_nSize; ++n)
    {
        if(cChar == m_pStr[n])
        {
            nRet = n;
            break;
        }
    }

    return nRet;
}

const EC_CHAR& ECString::operator[](EC_U32 nPos) const
{
    return m_pStr[nPos];
}

ECString& ECString::operator=(const EC_PCHAR pStr)
{
    if(m_pStr)
    {
        delete []m_pStr;
        m_pStr = EC_NULL;
        m_nSize = 0;
    }
    
    if(pStr)
    {
        m_nSize = ECStringOP::StrLen(pStr);
        m_pStr = new EC_CHAR[m_nSize + 1];
        ECStringOP::StrCopy(m_pStr, pStr);
    }

    return (*this);
}

ECString& ECString::operator+(const EC_PCHAR pStr)
{
    if(pStr)
    {
        EC_U32 nSize = m_nSize + ECStringOP::StrLen(pStr);
        EC_PCHAR pTmp = new EC_CHAR[nSize + 1];
        ECStringOP::StrCopy(pTmp, m_pStr);
        ECStringOP::StrCopy(pTmp+m_nSize, pStr);
        delete []m_pStr;
        m_pStr = pTmp;
        m_nSize = nSize;
    }

    return (*this);
}

ECString& ECString::operator=(const ECString &rString)
{
    if(this == &rString)
        return (*this);

    if(m_pStr)
        delete []m_pStr;
    m_nSize = rString.m_nSize;
    if(m_nSize > 0)
    {
        m_pStr = new EC_CHAR[ECStringOP::StrLen(rString.m_pStr) + 1];
        if(m_pStr)
            ECStringOP::StrCopy(m_pStr, rString.m_pStr);
        else
            m_nSize = 0;
    }
    else
    {
        m_nSize = 0;
        m_pStr = EC_NULL;
    }
    return (*this);
}

ECString& ECString::operator+(const ECString &rString)
{
    if(rString.m_nSize > 0)
    {
        EC_U32 nSize = m_nSize + rString.m_nSize;
        EC_PCHAR pTmp = new EC_CHAR[nSize + 1];
		ECStringOP::StrCopy(pTmp, m_pStr);
        ECStringOP::StrCopy(pTmp+m_nSize, rString.m_pStr);
        delete []m_pStr;
        m_pStr = pTmp;
        m_nSize = nSize;
    }

    return (*this);
}

EC_BOOL operator<(const ECString &st1, const ECString &st2)
{
    return (ECStringOP::StrCompare(st1.m_pStr, st2.m_pStr)<0);
}

EC_BOOL operator>(const ECString &st1, const ECString &st2)
{
    return (ECStringOP::StrCompare(st1.m_pStr, st2.m_pStr)>0);
}

EC_BOOL operator>=(const ECString &st1, const ECString &st2)
{
    return (ECStringOP::StrCompare(st1.m_pStr, st2.m_pStr)>=0);
}

EC_BOOL operator<=(const ECString &st1, const ECString &st2)
{
    return (ECStringOP::StrCompare(st1.m_pStr, st2.m_pStr)<=0);
}

EC_BOOL operator==(const ECString &st1, const ECString &st2)
{
    return (ECStringOP::StrCompare(st1.m_pStr, st2.m_pStr)==0);
}
