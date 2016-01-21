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
* ECConfig.h
* This file for Common software configuration interface define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_CONFIG_H
#define EC_CONFIG_H

#include "ECFile.h"
#include "ECString.h"

#define CONFIG_ASSGINV_CHAR       '='
#define CONFIG_COMMENT_CHAR       '#'
#define CONFIG_ASSGINV_STR        "="
#define CONFIG_COMMENT_STR        "#"
#define CONFIG_MAX_ITEM_COUNT     256
#define CONFIG_MAX_ITEM_LENGTH   1024


typedef struct
{
    ECString m_sKey;
    ECString m_sVal;
} ECConfigItem;

class ECConfig
{
public:
    ECConfig(const EC_PCHAR pFilePath);
    ~ECConfig();
    EC_U32 WriteToFile();
    EC_U32 GetItemCount() const;
    EC_U32 GetValue(const EC_PCHAR pKey, EC_PCHAR pVal) const;
    EC_U32 SetValue(const EC_PCHAR pKey, const EC_PCHAR pVal);
    EC_U32 AddItem (const EC_PCHAR pKey, const EC_PCHAR pVal);
    EC_U32 DeleteItem(const EC_PCHAR pKey);
    ECConfigItem GetItem(EC_U32 nIndex) const;

private:
    ECString FindKey(const EC_PCHAR pStr) const;
    ECString FindVal(const EC_PCHAR pStr) const;

private:
    EC_U32          m_nCount;
    ECFile          m_sFile;
    ECConfigItem    m_pConfigItem[CONFIG_MAX_ITEM_COUNT];
};

#endif /* CONFIG_H */