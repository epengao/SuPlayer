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
 * ECConfig.cpp
 * This file for Common software configuration interface implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECError.h"
#include "ECConfig.h"
#include "ECStringOP.h"


ECConfig::ECConfig(const EC_PCHAR pFilePath)
:m_nCount(0)
,m_sFile(pFilePath)
{
    if(EC_Err_None == m_sFile.Open((EC_PCHAR)"rt"))
    {
        ECString pKey;
        ECString pVal;
        ECString sCfgStr;
        EC_CHAR pCfgStr[CONFIG_MAX_ITEM_LENGTH] = {0};

        EC_U32 nReadRet = m_sFile.ReadStrLine(pCfgStr, CONFIG_MAX_ITEM_LENGTH);
        while(EC_Err_None == nReadRet)
        {
            sCfgStr = pCfgStr;
            sCfgStr.Trim();
            sCfgStr.TrimEnd();
            if(m_nCount < CONFIG_MAX_ITEM_COUNT)
            {
                pKey = FindKey(sCfgStr.ToCStr());
                pVal = FindVal(sCfgStr.ToCStr());
                if(!pKey.IsNull() /*&& !pVal.IsNull()*/)
                {
                    m_pConfigItem[m_nCount].m_sKey = pKey;
                    m_pConfigItem[m_nCount].m_sVal = pVal;
                    m_nCount++;
                }
            }
            else
                return;

            nReadRet = m_sFile.ReadStrLine(pCfgStr, CONFIG_MAX_ITEM_LENGTH);
        };

        m_sFile.Close();
    }
}

ECConfig::~ECConfig()
{
}

EC_U32 ECConfig::WriteToFile()
{
    if(EC_Err_None == m_sFile.Open((EC_PCHAR)"rt"))
    {
        for(EC_U32 i = 0; i < m_nCount; ++i)
        {
            ECString strKey(m_pConfigItem[i].m_sKey);
            ECString strVal(m_pConfigItem[i].m_sVal);
            ECString strLine(strKey + strVal + (EC_PCHAR)"\n");
            m_sFile.WriteBuffer(strLine.ToCStr(), strLine.Length(), 1);
        };

        m_sFile.Close();
    }

    return EC_Err_None;
}

EC_U32 ECConfig::GetItemCount() const
{
    return m_nCount;
}

EC_U32 ECConfig::GetValue(const EC_PCHAR pKey, EC_PCHAR pVal) const
{
    for(EC_U32 i = 0; i < m_nCount; ++i)
    {
        if (0 == ECStringOP::StrCompare(m_pConfigItem[i].m_sKey.ToCStr(), pKey))
        {
            ECStringOP::StrCompare(pVal, m_pConfigItem[i].m_sVal.ToCStr());
            return EC_Err_None;
        }
    }

    return EC_Err_DataNotExist;
}

EC_U32 ECConfig::SetValue(const EC_PCHAR pKey, const EC_PCHAR pVal)
{
    for(EC_U32 i = 0; i < m_nCount; ++i)
    {
        if (0 == strcmp(m_pConfigItem[i].m_sKey.ToCStr(), pKey))
        {
            m_pConfigItem[i].m_sVal = pVal;
            return EC_Err_None;
        }
    }

    return EC_Err_DataNotExist;
}

EC_U32 ECConfig::AddItem(const EC_PCHAR pKey, const EC_PCHAR pVal)
{
    if(pKey && (m_nCount < CONFIG_MAX_ITEM_COUNT))
    {
        m_pConfigItem[m_nCount].m_sKey = pKey;
        m_pConfigItem[m_nCount].m_sVal = pVal;
        m_nCount++;
        return EC_Err_None;
    }

    return EC_Err_BadParam;
}

EC_U32 ECConfig::DeleteItem(const EC_PCHAR pKey)
{
    EC_S32 nFindPos = -1;
    for(EC_U32 i = 0; i < m_nCount; ++i)
    {
        if (0 == ECStringOP::StrCompare(m_pConfigItem[i].m_sKey.ToCStr(), pKey))
        {
            nFindPos = i;
            break;
        }
    }

    if(nFindPos < 0)
        return EC_Err_DataNotExist;
    if((m_nCount-1) == nFindPos)
    {
        m_nCount--;
        return EC_Err_None;
    }

    for(EC_U32 i = nFindPos; i < m_nCount-1; ++i)
        m_pConfigItem[i] = m_pConfigItem[i+1];
    m_nCount--;

    return EC_Err_None;
}

ECString ECConfig::FindKey(const EC_PCHAR pStr) const
{
    ECString sStr(pStr);
    EC_S32 nSize = sStr.FindChar(CONFIG_ASSGINV_CHAR);
    if(nSize >= 0)
        return ECString(pStr, nSize);
    else
    {
        if(pStr && (CONFIG_COMMENT_CHAR == pStr[0]))
            return ECString((EC_PCHAR)CONFIG_COMMENT_STR);
    }

    return ECString();
}

ECString ECConfig::FindVal(const EC_PCHAR pStr) const
{
    ECString sStr(pStr);
    EC_S32 nSize = sStr.FindChar(CONFIG_ASSGINV_CHAR);
    if(nSize >= 0)
    {
        ECString sVal(pStr+nSize+1);
        sVal.Trim();
        return sVal;
    }
    else
        if(pStr && (CONFIG_COMMENT_CHAR == pStr[0]))
            return ECString(pStr+1);

    return ECString();
}

ECConfigItem ECConfig::GetItem(EC_U32 nIndex) const
{
    if(nIndex < m_nCount)
        return m_pConfigItem[nIndex];
    return ECConfigItem();
}
