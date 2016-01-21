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
* ECFile.cpp
* This file for Common file operation interface implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "ECFile.h"
#include "ECError.h"
#include "ECStringOP.h"


ECFile::ECFile(EC_S32 nFD)
:m_nFD(nFD)
,m_pFile(EC_NULL)
,m_pFilePath(EC_NULL)
{
}

ECFile::ECFile(const EC_PCHAR pFilePath)
:m_nFD(-1)
,m_pFile(EC_NULL)
{
	EC_U32 nSize = ECStringOP::StrLen(pFilePath);
    m_pFilePath = new EC_CHAR[nSize+1];
    if(m_pFilePath)
        ECStringOP::StrCopy(m_pFilePath, pFilePath);
}

ECFile::~ECFile()
{
    if(m_pFilePath)
        delete m_pFilePath;
    if(m_pFile)
        fclose(m_pFile);
}

EC_U32 ECFile::Open(const EC_PCHAR pOpenType)
{
    EC_U32 nRet = EC_Err_None;
    if(EC_NULL == m_pFile)
    {
        if(m_nFD >= 0)
        {
            m_pFile = fdopen(m_nFD, pOpenType);
            if(m_pFile)
                nRet = EC_Err_None;
            else
                nRet = EC_Err_FileOpenFaild;
        }
        else if(m_pFilePath)
        {
            m_pFile = fopen(m_pFilePath, pOpenType);
            if(EC_NULL == m_pFile)
                nRet = EC_Err_FileOpenFaild;
        }
        else
            nRet = EC_Err_FileOpenFaild;
    }

    return nRet;
}

EC_U32 ECFile::Close()
{
    if(m_pFile)
    {
        fclose(m_pFile);
        m_pFile = EC_NULL;
    }

    return EC_Err_None;
}

EC_LONG ECFile::GetSize()
{
    EC_LONG nRet = 0;
    if(m_pFile)
    {
        EC_LONG nCurr = ftell(m_pFile);
        fseek(m_pFile, 0L, EC_FILE_SEEK_END);
        nRet = ftell(m_pFile);
        fseek(m_pFile, nCurr, EC_FILE_SEEK_SET);
    }
    return nRet;
}

EC_U32 ECFile::GetPath(EC_PCHAR pPathOut)
{
#ifdef EC_OS_Linux
    if(EC_NULL == pPathOut)
        return EC_Err_BadParam;

    EC_U32 nFD = -1;
    EC_U32 nRet = EC_Err_None;
    if(m_pFilePath)
    {
        ECStringOP::StrCopy(pPathOut, m_pFilePath);
        return nRet;
    }

    if(m_pFile)
        nFD = fileno(m_pFile);
    else if(m_nFD >= 0)
        nFD = m_nFD;
    else
        nRet = EC_Err_DataNotExist;

    if(nFD >= 0)
    {
        EC_CHAR pBuf[EC_FILE_MAX_PATH] = {0};  
        EC_CHAR pFilePath[EC_FILE_MAX_PATH] = {0};
        snprintf(pBuf, sizeof(pBuf), "/proc/%ld/fd/%d", (EC_LONG)getpid(), nFD);  
        if (readlink(pBuf, pFilePath, EC_FILE_MAX_PATH-1) != -1)
            ECStringOP::StrCopy(pPathOut, pFilePath);
    }

    return nRet;
#endif

    if(m_pFilePath)
    {
        ECStringOP::StrCopy(pPathOut, m_pFilePath);
    }
    return EC_Err_None;
}

EC_U32 ECFile::Flush()
{
    if(m_pFile)
    {
        fflush(m_pFile);
        return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}

EC_CHAR ECFile::ReadChar()
{
    if(m_pFile)
        return fgetc(m_pFile);
    
    return EC_FILE_EOF;
}

EC_U32 ECFile::WriteChar(EC_CHAR cChar)
{
    if(m_pFile)
    {
        fputc(cChar, m_pFile);
        return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}

EC_U32 ECFile::ReadStrLine(EC_PCHAR pStr, EC_U32 nSize)
{
    if(m_pFile)
    {
        EC_PCHAR pRet = fgets(pStr, nSize, m_pFile);
        if(pRet)
            return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}

EC_U32 ECFile::ReadBuffer(EC_BUFFER pBuf, EC_U32 nBufSize, EC_U32 nBufCount)
{
    if(m_pFile)
    {
        fread(pBuf, nBufSize, nBufCount, m_pFile);
        return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}

EC_U32 ECFile::WriteBuffer(EC_BUFFER pBuf, EC_U32 nBufSize, EC_U32 nBufCount)
{
    if(m_pFile)
    {
        fwrite(pBuf, nBufSize, nBufCount, m_pFile);
        return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}

EC_U32 ECFile::Seek(EC_S32 nOffset, EC_U32 nFromPos)
{
    if(m_pFile)
    {
        fseek(m_pFile, nOffset, nFromPos);
        return EC_Err_None;
    }

    return EC_Err_OperatorFaild;
}
