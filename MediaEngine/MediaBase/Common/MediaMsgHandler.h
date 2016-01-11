/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * MediaMsgHandler.h
 *
 * This file define the media message handler, which will handle
 * both media data flow message and framework control message.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef MEDIA_MSG_HANDLER_H
#define MEDIA_MSG_HANDLER_H

#include "ECType.h"
#include "ECMutex.h"
#include "ECRingQueue.h"
#include "ECMsgHandlerI.h"

#define MSG_QUEUE_MAX_SIZE 512

class MediaMsgHandler : public ECMsgHandlerI
{
public:
    virtual EC_VOID  DispatchMsg(void* pMsg = EC_NULL) = 0;

public:
    MediaMsgHandler(EC_U32 nMsgQMaxSize = MSG_QUEUE_MAX_SIZE);
    virtual ~MediaMsgHandler();
    virtual EC_U32 PushMsg(void* pMsg);
    virtual EC_U32 PopMsg(void** ppMsg);
    virtual EC_VOID CleanMsg();
    virtual EC_VOID DestroyMsg(void* pMsg);

protected:
	EC_U32                m_nMsgCount;
    ECMutex               m_mtxMsg;
    ECRingQueue<void*>*   m_pMsgQueue;
};

#endif /* MEDIA_MSG_HANDLER_H */