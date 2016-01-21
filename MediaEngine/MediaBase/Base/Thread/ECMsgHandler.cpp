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
* ECMsgHandler.cpp
*
* This file for thread message handler interface.
* Any module want to use thread to dispathch message, 
* need to implement this.Here we do part of the implementation
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECAutoLock.h"
#include "ECMsgHandler.h"


ECMsgHandler::ECMsgHandler(EC_U32 nMsgQMaxSize)
{
    m_pMsgQueue = new ECRingQueue<void*>(nMsgQMaxSize);
}

ECMsgHandler::~ECMsgHandler()
{
    if(m_pMsgQueue) delete m_pMsgQueue;
}

EC_U32 ECMsgHandler::PushMsg(void* pMsg)
{
    EC_U32 nRet = EC_Err_None;
    if (m_pMsgQueue)
    {
        ECAutoLock Lock(&m_mtxMsgQueue);
        nRet = m_pMsgQueue->Push(pMsg);
    }
    else 
        nRet = EC_Err_Memory_Overflow;

    return nRet;
}

EC_U32 ECMsgHandler::PopMsg(void **ppMsg)
{
    EC_U32 nRet = EC_Err_None;
    if(m_pMsgQueue)
    {
        ECAutoLock Lock(&m_mtxMsgQueue);
        nRet = m_pMsgQueue->Pop(ppMsg);
    }
    return nRet;
}

EC_VOID ECMsgHandler::CleanMsg()
{
    if (m_pMsgQueue)
    {
        ECAutoLock Lock(&m_mtxMsgQueue);
        while (!m_pMsgQueue->IsEmpty())
        {
            void* pMsg = EC_NULL;
            m_pMsgQueue->Pop(&pMsg);
            DestroyMsg(pMsg);
        }
        m_pMsgQueue->Clean();
    }
}