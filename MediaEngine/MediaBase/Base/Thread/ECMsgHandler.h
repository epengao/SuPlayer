/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECMsgHandler.h
 *
 * This file for thread message handler interface a simple implementaion
 * Here we not implement the Dispatch() method, for exactly App use will
 * implement this method. It depends on App requirement.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_MSG_HANDLER_H
#define EC_MSG_HANDLER_H

#include "ECType.h"
#include "ECMutex.h"
#include "ECRingQueue.h"
#include "ECMsgHandlerI.h"

#define MSG_QUEUE_MAX_SIZE 512

class ECMsgHandler : public ECMsgHandlerI
{
public:
    virtual EC_VOID  DispatchMsg(void* pMsg = EC_NULL) = 0;

public:
    ECMsgHandler(EC_U32 nMsgQMaxSize = MSG_QUEUE_MAX_SIZE);
    virtual ~ECMsgHandler();
    virtual EC_U32 PushMsg(void* pMsg);
    virtual EC_U32 PopMsg(void** ppMsg);
    virtual EC_VOID CleanMsg();
    virtual EC_VOID DestroyMsg(void* pMsg){};

protected:
    ECMutex               m_mtxMsgQueue;
    ECRingQueue<void*>*   m_pMsgQueue;
};

#endif /* EC_MSG_HANDLER_H */