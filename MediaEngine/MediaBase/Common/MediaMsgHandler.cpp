/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * MediaMsgHandler.cpp
 *
 * This file for MediaMsgHandler implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECAutoLock.h"
#include  "MediaCommon.h"
#include "MediaMsgHandler.h"


MediaMsgHandler::MediaMsgHandler(EC_U32 nMsgQMaxSize)
:m_nMsgCount(0)
{
    m_pMsgQueue = new ECRingQueue<void*>(nMsgQMaxSize);
}

MediaMsgHandler::~MediaMsgHandler()
{
    /* Exit thread, clear Ctrl Msg*/
    {
    ECAutoLock Lock(&m_mtxMsg);
    while (!m_pMsgQueue->IsEmpty())
    {
        void* pMsg = EC_NULL;
        m_pMsgQueue->Pop(&pMsg);
        DestroyMsg(pMsg);
        }
        m_pMsgQueue->Clean();
    }
    delete m_pMsgQueue;
}

EC_U32 MediaMsgHandler::PushMsg(void* pMsg)
{
    if (pMsg)
    {
        ECAutoLock Lock(&m_mtxMsg);
        return m_pMsgQueue->Push(pMsg);
    }
    else
        m_nMsgCount++;

    return EC_Err_None;
}

EC_U32 MediaMsgHandler::PopMsg(void **ppMsg)
{
    /* High priority for Ctrl Msg */
    EC_U32 nRet = EC_Err_None;
    {
        ECAutoLock Lock(&m_mtxMsg);
        if (!m_pMsgQueue->IsEmpty())
        {
            nRet = m_pMsgQueue->Pop(ppMsg);
            return nRet;
        }
    }

    if (m_nMsgCount > 0)
    {
        m_nMsgCount--;
        nRet = EC_Err_None;
    }
    else
        nRet = EC_Err_ContainerEmpty;

    return nRet;
}

EC_VOID MediaMsgHandler::CleanMsg()
{
    /* Here we just clear Media
       Data msg, keep Ctrl Msg */
    m_nMsgCount = 0;
}

EC_VOID MediaMsgHandler::DestroyMsg(void* pMsg)
{
    if (EC_NULL == pMsg) return;

    MediaEngMsg *pMediaMsg = (MediaEngMsg*)pMsg;
    switch (pMediaMsg->nCmd)
    {
        case MediaEngCommand_Seek:
        {
            EC_U32 *pParam = (EC_U32*)pMediaMsg->pParam;
            delete pParam;
            break;
        }
        default: break;
    }

    if (pMediaMsg) delete pMediaMsg;
}
