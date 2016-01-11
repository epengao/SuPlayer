/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ECArray.h
 * define a static length Array which can store any type of data.
 *
 * Eamil:  epengao@126.com
 * Author: Peter Gao
 * Version: First initinal version.
 * --------------------------------------------------------------------
 */

#ifndef EC_ARRAY_H
#define EC_ARRAY_H

#include "ECError.h"
#include "ECType.h"
#include "ECCompare.h"

#define ECARRAY_DEFAULT_MAX_SIZE    512

template<typename T>
class ECArray
{
public:
    ECArray(EC_U32 maxSize = ECARRAY_DEFAULT_MAX_SIZE,
            ECCompare<T> *pCompare = EC_NULL);
    ~ECArray();
    EC_U32 InsertToHead(const T data);
    EC_U32 InsertToTail(const T data);
    EC_U32 InsertAtIndex(const T data, EC_U32 index);
    EC_U32 DeleteFromHead();
    EC_U32 DeleteFromTail();
    EC_U32 DeleteAtIndex(EC_U32 index);
    EC_U32 GetItemFromHead(T* pData)               const;
    EC_U32 GetItemFromTail(T* pData)               const;
    EC_U32 GetItemAtIndex(T* pData, EC_U32 index)  const;
    EC_U32 GetItemsCount() const {return m_nItemCount;}
    EC_U32 GetMaxSize() const {return m_nMaxSize;}
    EC_VOID SetCompare(ECCompare<T> *pCompare) {m_pCompare = pCompare;}
    EC_U32 Sort(EC_BOOL bSortType = EC_TRUE);

private:
    T*              m_pDatas;
    EC_U32          m_nItemCount;
    EC_U32          m_nMaxSize;
    ECCompare<T>*   m_pCompare;
};

template<typename T>
ECArray<T>::ECArray(EC_U32 maxSize,
                    ECCompare<T> *pCompare)
:m_nItemCount(0)
,m_nMaxSize(maxSize)
,m_pCompare(pCompare)
{
    m_pDatas = new T[m_nMaxSize];
}

template<typename T>
ECArray<T>::~ECArray()
{
    if(m_pDatas)
        delete []m_pDatas;
}

template<typename T>
EC_U32 ECArray<T>::InsertToHead(const T data)
{
    if(m_nItemCount >= m_nMaxSize)
        return EC_Err_ContainerFull;

    for(EC_U32 i=0; i<m_nItemCount; ++i)
        m_pDatas[i+1] = m_pDatas[i];

    m_pDatas[0] = data;
    m_nItemCount++;
    
    return EC_Err_None;
}

template<typename T>
EC_U32 ECArray<T>::InsertToTail(const T data)
{
    if(m_nItemCount >= m_nMaxSize)
        return EC_Err_ContainerFull;
    
    m_pDatas[m_nItemCount] = data;
    m_nItemCount++;
    
    return EC_Err_None;
}

template<typename T>
EC_U32 ECArray<T>::InsertAtIndex(const T data, EC_U32 index)
{
    if(m_nItemCount >= m_nMaxSize)
        return EC_Err_ContainerFull;

    EC_U32 nRet = EC_Err_None;
    if((index>0) && (index<m_nItemCount))
    {
        for(EC_U32 i=m_nItemCount-1; i>=index; --i)
            m_pDatas[i+1]=m_pDatas[i];
        m_pDatas[index] = data;
        m_nItemCount++;
    }
    else if(index == 0)
        nRet = InsertToHead(data);
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

template<typename T>
EC_U32 ECArray<T>::DeleteFromHead()
{
    return DeleteAtIndex(0);
}

template<typename T>
EC_U32 ECArray<T>::DeleteFromTail()
{
    return DeleteAtIndex(m_nItemCount-1);
}

template<typename T>
EC_U32 ECArray<T>::DeleteAtIndex(EC_U32 index)
{
    EC_U32 nRet = EC_Err_None;
    if((index>=0) && (index<m_nItemCount))
    {
        for(EC_U32 i=index; i<m_nItemCount; ++i)
            m_pDatas[i] = m_pDatas[i+1];
        m_nItemCount--;
    }
    else
        nRet = EC_Err_BadParam;

    return nRet;
}

template<typename T>
EC_U32 ECArray<T>::GetItemFromHead(T* pData) const
{
    return GetItemAtIndex(pData, 0);
}

template<typename T>
EC_U32 ECArray<T>::GetItemFromTail(T* pData) const
{
    return GetItemAtIndex(pData, m_nItemCount-1);
}

template<typename T>
EC_U32 ECArray<T>::GetItemAtIndex(T* pData, EC_U32 index) const
{
    EC_U32 nRet = EC_Err_None;
    if((index>=0) && (index<m_nItemCount))
        *pData = m_pDatas[index];
    else
        nRet = EC_Err_BadParam;
    
    return nRet;
}

template<typename T>
EC_U32 ECArray<T>::Sort(EC_BOOL bSortType /* EC_TRUE*/)
{
    if(m_pCompare)
    {
        for(EC_U32 i=0; i<m_nItemCount-1; ++i)
        {
            for(EC_U32 j=0; j<m_nItemCount-1; ++j)
            {
                EC_S32 bCompareResult = m_pCompare->Compare(&m_pDatas[j], &m_pDatas[j+1]);
                if( (bSortType && (bCompareResult == EC_GREATER))
                    || (!bSortType && (bCompareResult == EC_LESSTHEN)) )
                {
                    T data = m_pDatas[j];
                    m_pDatas[j] = m_pDatas[j+1];
                    m_pDatas[j+1] = data;
                }
            }
        }
        return EC_Err_None;
    }
    else
        return EC_Err_NotImplement;
}

#endif /* EC_ARRAY_H */
