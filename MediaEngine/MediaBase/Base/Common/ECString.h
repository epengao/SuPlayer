/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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
