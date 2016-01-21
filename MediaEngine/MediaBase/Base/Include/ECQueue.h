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
* ECQueue.h
*
* define a Queue which can store any type of data.
*
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_QUEUE_H
#define EC_QUEUE_H

#include "ECMutableArray.h"


template<typename T>
class ECQueue
{
public:
    ECQueue();
    ~ECQueue();
public:
    EC_U32 Push(T data);
    EC_U32 Pop(T *data);
    EC_U32 Front(T *pOutData) const;
    EC_U32 Back(T* pOutData)  const;
    EC_BOOL IsEmpty() const;
    EC_U32  Count() const;

private:
    ECMutableArray<T>*  m_pContainer;
};

template<typename T>
ECQueue<T>::ECQueue()
{
    m_pContainer = new ECMutableArray<T>;
}

template<typename T>
ECQueue<T>::~ECQueue()
{
    if(m_pContainer)
        delete m_pContainer;
}

template<typename T>
EC_U32 ECQueue<T>::Push(T data)
{
    if(m_pContainer)
        return m_pContainer->InsertToTail(data);
    else
        return EC_Err_Memory_Overflow;
}

template<typename T>
EC_U32 ECQueue<T>::Pop(T *pOutData)
{
    EC_U32 nRet = EC_Err_None;

    if(m_pContainer)
    {
        nRet = m_pContainer->GetItemFromHead(pOutData);
        if(nRet == EC_Err_None)
            return m_pContainer->DeleteFromHead();
    }
    else
        nRet = EC_Err_Memory_Overflow;
    
    return nRet;
}

template<typename T>
EC_U32 ECQueue<T>::Front(T *pOutData) const
{
    EC_U32 nRet = EC_Err_None;
    
    if(m_pContainer)
    {
        nRet = m_pContainer->GetItemFromHead(pOutData);
    }
    else
        nRet = EC_Err_Memory_Overflow;
    
    return nRet;
}

template<typename T>
EC_U32 ECQueue<T>::Back(T *pOutData) const
{
    EC_U32 nRet = EC_Err_None;
    
    if(m_pContainer)
    {
        nRet = m_pContainer->GetItemFromTail(pOutData);
    }
    else
        nRet = EC_Err_Memory_Overflow;
    
    return nRet;
}

template<typename T>
EC_BOOL ECQueue<T>::IsEmpty() const
{
    EC_BOOL bRet = EC_TRUE;

    if(m_pContainer)
    {
        bRet = (m_pContainer->GetItemsCount() == 0);
    }
    
    return bRet;
}

template<typename T>
EC_U32 ECQueue<T>::Count() const
{
    EC_U32 count = 0;
    if(m_pContainer)
        count = m_pContainer->GetItemsCount();
    
    return count;
}

#endif /* EC_STACK_H */
