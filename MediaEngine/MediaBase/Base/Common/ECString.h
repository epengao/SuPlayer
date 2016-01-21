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
* This file for EC project common string interface define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_STRING_H
#define EC_STRING_H

#include "ECType.h"


class ECString
{
public:
    ECString();
    ~ECString();
    ECString(EC_CONST_PCHAR pStr);
    ECString(const ECString &rString);
    ECString(const EC_PCHAR pStr, EC_U32 nSize);
    ECString(const ECString &rString, EC_U32 nSize);

    EC_U32 Trim();
    EC_U32 TrimEnd();
    EC_U32 Length() const;
    EC_BOOL IsNull() const;
    EC_PCHAR ToCStr() const;
    EC_CHAR& operator[](EC_U32 nPos);
    EC_S32 FindChar(const EC_CHAR cChar) const;
    const EC_CHAR& operator[](EC_U32 nPos) const;
    ECString& operator=(const EC_PCHAR pStr);
    ECString& operator+(const EC_PCHAR pStr);
    ECString& operator=(const ECString &rString);
    ECString& operator+(const ECString &rString);

public:
    friend EC_BOOL operator <(const ECString &st1, const ECString &st2);
    friend EC_BOOL operator >(const ECString &st1, const ECString &st2);
    friend EC_BOOL operator<=(const ECString &st1, const ECString &st2);
    friend EC_BOOL operator>=(const ECString &st1, const ECString &st2);
    friend EC_BOOL operator==(const ECString &st1, const ECString &st2);

private:
    EC_PCHAR m_pStr;
    EC_U32   m_nSize;
};

#endif /* EC_STRING_H   */
