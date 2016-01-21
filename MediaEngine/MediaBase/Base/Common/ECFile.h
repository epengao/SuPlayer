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
* ECFile.h
* This file for Common file operation interface define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_FILE_OP_H
#define EC_FILE_OP_H

#include <stdio.h>
#include "ECType.h"

#define EC_FILE_MAX_PATH        1024

#define EC_FILE_OPEN_RT         "rt"
#define EC_FILE_OPEN_WT         "wt"
#define EC_FILE_OPEN_AT         "at"
#define EC_FILE_OPEN_RB         "rb"
#define EC_FILE_OPEN_WB         "wb"
#define EC_FILE_OPEN_AB         "ab"
#define EC_FILE_OPEN_RWT        "rt+"
#define EC_FILE_OPEN_WRT        "wt+"
#define EC_FILE_OPEN_RWB        "rb+"
#define EC_FILE_OPEN_WRB        "wb+"
#define EC_FILE_OPEN_RWAT       "at+"
#define EC_FILE_OPEN_RWAB       "ab+"

#define EC_FILE_EOF             EOF
#define EC_FILE_SEEK_SET        SEEK_SET
#define EC_FILE_SEEK_CUR        SEEK_CUR
#define EC_FILE_SEEK_END        SEEK_END


class ECFile
{
public:
    ECFile(EC_S32 nFD);
    ECFile(const EC_PCHAR pFilePath);
    ~ECFile();

    EC_U32 Open(const EC_PCHAR pOpenType);
    EC_U32 Close();
    EC_LONG GetSize();
    EC_U32 GetPath(EC_PCHAR pPathOut);
    EC_U32 Flush();
    EC_CHAR ReadChar();
    EC_U32 WriteChar(EC_CHAR cChar);
    EC_U32 ReadStrLine(EC_PCHAR pStr, EC_U32 nSize);
    EC_U32 ReadBuffer(EC_BUFFER pBuf, EC_U32 nBufSize, EC_U32 nBufCount);
    EC_U32 WriteBuffer(EC_BUFFER pBuf, EC_U32 nBufSize, EC_U32 nBufCount);
    EC_U32 Seek(EC_S32 nOffset, EC_U32 nFromPos);

private:
    FILE*       m_pFile;
    EC_S32      m_nFD;
    EC_PCHAR    m_pFilePath;
};

#endif /* FILE_OP_H */