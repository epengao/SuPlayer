/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECThread.cpp
 * This file for EC thread interface & encapsulation implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECError.h"
#include "ECOSUtil.h"
#include "ECThread.h"
#include "ECStringOP.h"


ECThread::ECThread(
                   ECMsgHandlerI* pMsgHandler,
                   EC_PCHAR pThreadName
                  )
:m_strName(pThreadName)
,m_nStatus(ECThreadStatus_Init)
,m_pMsgHandler(pMsgHandler)
,m_semStoped(0, 1)
{
#ifdef EC_OS_Win32
    m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncEntry, this, 0, &m_nThreadID);
#elif defined EC_OS_Linux
    pthread_create(&m_ThreadHandle, NULL, ThreadFuncEntry, this);
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
    m_nThreadID = pthread_create(&m_ThreadHandle, NULL, ThreadFuncEntry, this);
#elif defined EC_OS_Android
/* TODO */
#endif
}

ECThread::~ECThread()
{
    if(ECThreadStatus_Stop != m_nStatus)
        Stop();

#ifdef EC_OS_Win32
    CloseHandle(m_hThread);
#elif defined EC_OS_Linux
    pthread_join(m_ThreadHandle, NULL);
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
    //pthread_join(m_ThreadHandle, NULL);
#elif defined EC_OS_Android
/* TODO */
#endif
}

void ECThread::Run()
{
    ECThreadStatus oldStatus = m_nStatus;
    m_nStatus = ECThreadStatus_Run;

    if(ECThreadStatus_Init == oldStatus)
        m_sigInit.Send();
    else if(ECThreadStatus_Pause == oldStatus)
        m_sigPause.Send();
    else if(ECThreadStatus_Stop == oldStatus)
        m_nStatus = oldStatus;
}

void ECThread::Pause()
{
    ECThreadStatus oldStatus = m_nStatus;
    m_nStatus = ECThreadStatus_Pause;
    
    if(ECThreadStatus_Init == oldStatus)
        m_sigInit.Send();
    else if(ECThreadStatus_Run == oldStatus)
        m_semMsgSignal.SendSIGNAL();
    else if(ECThreadStatus_Stop == oldStatus)
        m_nStatus = oldStatus;
}

void ECThread::Stop()
{
    ECThreadStatus oldStatus = m_nStatus;
    m_nStatus = ECThreadStatus_Stop;
    if(ECThreadStatus_Stop == oldStatus)
        return;
    else if(ECThreadStatus_Init == oldStatus)
        m_sigInit.Send();
    else if (ECThreadStatus_Pause == oldStatus)
        m_sigPause.Send();
    else if(ECThreadStatus_Run == oldStatus)
        m_semMsgSignal.SendSIGNAL();

    m_semStoped.WaitSIGNAL();
    ClearMsg();
}

void ECThread::ClearMsg()
{
    if(m_pMsgHandler) m_pMsgHandler->CleanMsg();
}

EC_U32 ECThread::PushMsg(void* pMsg)
{
    if(ECThreadStatus_Run != m_nStatus)
        return EC_Err_OperatorFaild;

    EC_U32 nRet = EC_Err_None;
    if(m_pMsgHandler)
    {
        nRet = m_pMsgHandler->PushMsg(pMsg);
        if(EC_Err_None == nRet)
        {
            m_semMsgSignal.SendSIGNAL();
        }
    }
    return nRet;
}

void* ECThread::ThreadFuncEntry(void* pArg)
{
    if(EC_NULL == pArg)
        return EC_NULL;

    ECThread* pThreadHandle = (ECThread*)pArg;
    while(EC_TRUE)
    {
        switch (pThreadHandle->m_nStatus)
        {
            case ECThreadStatus_Init:
            {
                pThreadHandle->m_sigInit.Wait();
            }
            break;

            case ECThreadStatus_Run:
            {
                if (pThreadHandle->m_pMsgHandler)
                {
                    void *pMsg = EC_NULL;
                    EC_U32 nRet = pThreadHandle->m_pMsgHandler->PopMsg(&pMsg);
                    if (EC_Err_None == nRet)
                    {
                        pThreadHandle->m_pMsgHandler->DispatchMsg(pMsg);
                        pThreadHandle->m_pMsgHandler->DestroyMsg(pMsg);
                    }
                }
                pThreadHandle->m_semMsgSignal.WaitSIGNAL(THREAD_WAIT_SIG_TIMEOUT);
            }
            break;

            case ECThreadStatus_Pause:
            {
                pThreadHandle->m_sigPause.Wait();
            }
            break;

            case ECThreadStatus_Stop:
            {
                pThreadHandle->m_semStoped.SendSIGNAL();
                return EC_NULL;
            }
            break;

            default: return EC_NULL;
        }
    }
}
