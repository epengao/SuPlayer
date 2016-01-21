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