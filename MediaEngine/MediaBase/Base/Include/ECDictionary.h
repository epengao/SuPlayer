/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ECDictionary.h
 *
 * define a Dictionary which can store any type of data.
 *
 * [Note:] Key class type, must have the == opration implementation
 *
 * Eamil:  epengao@126.com
 * Author: Peter Gao
 * Version: First initinal version.
 * --------------------------------------------------------------------
 */

#ifndef EC_DICTIONARY_H
#define EC_DICTIONARY_H

#include "ECMutableArray.h"


template<typename KeyT, typename ValT>
class ECDictionary
{
public:
    ECDictionary();
    ~ECDictionary();

public:
    EC_U32 AddObject(const KeyT key, const ValT value);
    EC_U32 DeleteObject(const KeyT key);
    EC_U32 GetObject(const KeyT key, ValT* value) const;
    EC_BOOL IsEmpty() const;
    EC_U32  Count() const;
    EC_VOID Reset();
private:
    EC_U32 FindObjectPos(const KeyT key) const;

private:
    ECMutableArray<ECPairNode<KeyT,ValT>>*  m_pContainer;
};

template<typename KeyT, typename ValT>
ECDictionary<KeyT,ValT>::ECDictionary()
{
    m_pContainer = new ECMutableArray<ECPairNode<KeyT,ValT>>();
}

template<typename KeyT, typename ValT>
ECDictionary<KeyT,ValT>::~ECDictionary()
{
    if(m_pContainer) delete m_pContainer;
}


template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::AddObject(const KeyT key, const ValT value)
{
    if(m_pContainer)
    {
        return m_pContainer->InsertToTail(ECPairNode<KeyT,ValT>(key,value));
    }
    else
        return EC_Err_Memory_Overflow;
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::DeleteObject(const KeyT key)
{
    EC_U32 nPos = FindObjectPos(key);
    if(m_pContainer) return m_pContainer->DeleteAtIndex(nPos);
    else return EC_Err_Memory_Overflow;
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::GetObject(const KeyT key, ValT* pValue) const
{
    EC_U32 nPos = FindObjectPos(key);
    if(m_pContainer)
    {
        ECPairNode<KeyT,ValT> pare;
        EC_U32 nRet = m_pContainer->GetItemAtIndex(&pare, nPos);
        if(EC_Err_None==nRet)
        {
            *pValue = pare.m_sVal;
            return EC_Err_None;
        }
        else return nRet;
    }
    else
        return EC_Err_Memory_Overflow;
}

template<typename KeyT, typename ValT>
EC_BOOL ECDictionary<KeyT,ValT>::IsEmpty() const
{
    if(m_pContainer)
    {
        return (0==m_pContainer->GetItemsCount());
    }
    else return EC_TRUE;
}

template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::Count() const
{
    if(m_pContainer) return m_pContainer->GetItemsCount();
    else return 0;
}

template<typename KeyT, typename ValT>
EC_VOID ECDictionary<KeyT,ValT>::Reset()
{
    if(m_pContainer)
    {
        delete m_pContainer;
        m_pContainer = new ECMutableArray<ECPairNode<KeyT,ValT>>();
    }
}

/* privare function */
template<typename KeyT, typename ValT>
EC_U32 ECDictionary<KeyT,ValT>::FindObjectPos(const KeyT key) const
{
    EC_U32 nPos = EC_U32_MAX;

    if(m_pContainer)
    {
        EC_U32 nCount = m_pContainer->GetItemsCount();
        ECPairNode<KeyT,ValT> pare;
        for(EC_U32 i=0; i<nCount; ++i)
        {
            EC_U32 nRet = m_pContainer->GetItemAtIndex(&pare, i);
            if((EC_Err_None==nRet) && (key==pare.m_sKey))
            {
                nPos = i;
                break;
            }
        }
    }
    
    return nPos;
}


#endif /* EC_DICTIONARY_H */
