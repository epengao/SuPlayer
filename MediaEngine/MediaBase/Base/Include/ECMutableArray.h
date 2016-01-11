/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ECMutableArray.h
 *
 * define a Mutable Array which can store any type of data.
 *
 * Eamil:  epengao@126.com
 * Author: Peter Gao
 * Version: First initinal version.
 * --------------------------------------------------------------------
 */

#ifndef EC_MUTABLE_ARRAY_H
#define EC_MUTABLE_ARRAY_H

#include "ECNode.h"
#include "ECError.h"
#include "ECCompare.h"

#define ECARRAY_DEFAULT_MAX_SIZE    512

template<typename T>
class ECMutableArray
{
public:
    ECMutableArray(ECCompare<T> *pCompare = EC_NULL);
    ~ECMutableArray();
    EC_U32 InsertToHead(const T data);
    EC_U32 InsertToTail(const T data);
    EC_U32 InsertAtIndex(const T data, EC_U32 index);
    EC_U32 DeleteFromHead();
    EC_U32 DeleteFromTail();
    EC_U32 DeleteAtIndex(EC_U32 index);
    EC_U32 GetItemFromHead(T* pData)               const;
    EC_U32 GetItemFromTail(T* pData)               const;
    EC_U32 GetItemAtIndex(T* pData, EC_U32 index)  const;
    EC_U32 GetItemsCount() const;
    EC_VOID SetCompare(ECCompare<T> *pCompare) {m_pCompare = pCompare;}
    EC_U32 Sort(EC_BOOL bSortType = EC_TRUE);

private:
    ECNode<T>*      m_pHeader;
    ECCompare<T>*      m_pCompare;
};

template<typename T>
ECMutableArray<T>::ECMutableArray(ECCompare<T> *pCompare)
:m_pHeader(EC_NULL)
,m_pCompare(pCompare)
{
}

template<typename T>
ECMutableArray<T>::~ECMutableArray()
{
    ECNode<T>* node = m_pHeader;
    while(node!=EC_NULL)
    {
        ECNode<T>* tmp = node->m_pNext;
        delete node;
        node = tmp;
    }
    m_pHeader = EC_NULL;
}

template<typename T>
EC_U32 ECMutableArray<T>::InsertToHead(const T data)
{
    ECNode<T>* pNode = new ECNode<T>(data);
    pNode->m_pNext = m_pHeader;
    m_pHeader = pNode;
    
    return EC_Err_None;
}

template<typename T>
EC_U32 ECMutableArray<T>::InsertToTail(const T data)
{
    if(m_pHeader==EC_NULL)
        return InsertToHead(data);

    ECNode<T>* node = m_pHeader;
    while(node && node->m_pNext)
        node = node->m_pNext;
    ECNode<T>* pNode = new ECNode<T>(data);
    node->m_pNext = pNode;

    return EC_Err_None;
    
}

template<typename T>
EC_U32 ECMutableArray<T>::InsertAtIndex(const T data, EC_U32 index)
{
    EC_U32 nRet = EC_Err_None;
    if( (index>0) && (index<GetItemsCount()) )
    {
        ECNode<T>* node = m_pHeader;
        for(EC_U32 i=0; i<index-1; ++i)
        {
            node = node->m_pNext;
        }
        ECNode<T>* pNode = new ECNode<T>(data, node->m_pNext);
        node->m_pNext = pNode;
    }
    else if(index == 0)
        nRet = InsertToHead(data);
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

template<typename T>
EC_U32 ECMutableArray<T>::DeleteFromHead()
{
    if(m_pHeader)
    {
        ECNode<T>* node = m_pHeader;
        m_pHeader = m_pHeader->m_pNext;
        delete node;
        return EC_Err_None;
    }
    
    return EC_Err_ContainerEmpty;
}

template<typename T>
EC_U32 ECMutableArray<T>::DeleteFromTail()
{
    EC_U32 nRet = EC_Err_None;

    EC_U32 nCount = GetItemsCount();
    if(nCount == 0)
        nRet = EC_Err_ContainerEmpty;
    else if(nCount == 1)
        nRet = DeleteFromHead();
    if(nCount >= 2)
    {
        ECNode<T>* node = m_pHeader;
        for(EC_U32 i=0; i<nCount-2; ++i)
            node = node->m_pNext;
        delete node->m_pNext;
        node->m_pNext = EC_NULL;
    }
    
    return nRet;
}

template<typename T>
EC_U32 ECMutableArray<T>::DeleteAtIndex(EC_U32 index)
{
    EC_U32 nRet = EC_Err_None;

    EC_U32 nCount = GetItemsCount();
    if( (index>0) && (index<nCount-1) )
    {
        ECNode<T>* node = m_pHeader;
        for(EC_U32 i=0; i<index-1; ++i)
            node = node->m_pNext;
        ECNode<T>* deleNode = node->m_pNext;
        node->m_pNext = deleNode->m_pNext;
        delete deleNode;
    }
    else if(index == 0)
        nRet = DeleteFromHead();
    else if(index == (nCount-1))
        nRet = DeleteFromTail();
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

template<typename T>
EC_U32 ECMutableArray<T>::GetItemFromHead(T* pData) const
{
    return GetItemAtIndex(pData, 0);
}

template<typename T>
EC_U32 ECMutableArray<T>::GetItemFromTail(T* pData) const
{
    return GetItemAtIndex(pData, GetItemsCount()-1);
}

template<typename T>
EC_U32 ECMutableArray<T>::GetItemAtIndex(T* pData, EC_U32 index) const
{
    EC_U32 nRet = EC_Err_None;

    if(pData)
    {
        EC_U32 nCount = GetItemsCount();
        if((index>=0) && (index<nCount))
        {
            ECNode<T>* node = m_pHeader;
            for(EC_U32 i=0; i<index; ++i)
                node = node->m_pNext;
            *pData = node->m_sData;
        }
    }
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

template<typename T>
EC_U32 ECMutableArray<T>::GetItemsCount() const
{
    EC_U32 nCount = 0;

    ECNode<T>* node = m_pHeader;
    while(node!=EC_NULL)
    {
        node = node->m_pNext;
        nCount++;
    }
    
    return nCount;
}

template<typename T>
EC_U32 ECMutableArray<T>::Sort(EC_BOOL bSortType /* EC_TRUE*/)
{
    /* TODO */
}

#endif /* EC_MUTABLE_ARRAY_H */
