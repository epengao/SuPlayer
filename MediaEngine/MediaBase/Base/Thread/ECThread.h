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
* ECThread.h
* This file for EC thread define and encapsulation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_THREAD_H
#define EC_THREAD_H

#include "ECString.h"
#include "ECSignal.h"
#include "ECSemaphore.h"
#include "ECMsgHandlerI.h"

#ifdef EC_OS_Win32
#include <windows.h>
#else
#include <pthread.h>
#endif

typedef enum
{
    ECThreadStatus_Init,
    ECThreadStatus_Run,
    ECThreadStatus_Pause,
    ECThreadStatus_Stop,
    ECThreadStatus_Unknow = EC_U16_MAX,
} ECThreadStatus;

#define THREAD_EXIT_WAIT_TIME    10
#define THREAD_EXIT_TRY_TIMES    100
#define THREAD_WAIT_SIG_TIMEOUT  200

class ECThread
{
public:
    ECThread(
             ECMsgHandlerI* pMsgHandler,
             EC_PCHAR pThreadName = EC_NULL
            );
    ~ECThread();

    void Run();
    void Pause();
    void Stop();
    void ClearMsg();
    EC_U32 PushMsg(void* pMsg = NULL);

private:
    static void* ThreadFuncEntry(void* pArg);

private:
    ECString            m_strName;
    ECThreadStatus      m_nStatus;
    ECSemaphore         m_semMsgSignal;
    ECSemaphore         m_semStoped;
    ECMsgHandlerI*      m_pMsgHandler;
    ECSignal            m_sigInit;
    ECSignal            m_sigPause;

#ifdef EC_OS_Win32
    DWORD          m_nThreadID;
    HANDLE         m_hThread;
#elif defined EC_OS_Linux
    pthread_t      m_ThreadHandle;
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    EC_S32         m_nThreadID;
    pthread_t      m_ThreadHandle;
#elif defined EC_OS_Android
    /* TODO */
#endif
};

#endif /* EC_THREAD_H */
