/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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