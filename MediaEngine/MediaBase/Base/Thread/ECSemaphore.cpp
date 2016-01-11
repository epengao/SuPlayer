/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECSemaphore.h
 * This file for ECSemaphore interface implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECOSUtil.h"
#include "ECStringOP.h"
#include "ECSemaphore.h"


ECSemaphore::ECSemaphore(EC_U32 nInitSig, /*0*/
                         EC_U32 nMaxSig   /*EC_MAX_U16*/)
{
#ifdef EC_OS_Win32
    m_hSemaphore = CreateSemaphore
                   (
                      EC_NULL,  // default security attributes
                      nInitSig,  // initial count
                      nMaxSig,   // maximum count
                      EC_NULL   // unnamed semaphore
                   );
#else
    m_pSemaphoreName = new EC_CHAR[128];
    ECStringOP::IntToStr(m_pSemaphoreName, (EC_U32)(ecGetSystemTimeU()%EC_U32_MAX));
    m_hSemaphore = sem_open(m_pSemaphoreName, O_CREAT, 644, nInitSig);
#endif
}

ECSemaphore::~ECSemaphore()
{
#ifdef EC_OS_Win32
    CloseHandle(m_hSemaphore);
#else
    sem_close(m_hSemaphore);
    sem_unlink(m_pSemaphoreName);
    if(m_pSemaphoreName) delete m_pSemaphoreName;
#endif
}

EC_BOOL ECSemaphore::SendSIGNAL()
{
#ifdef EC_OS_Win32
    return ReleaseSemaphore(m_hSemaphore, 1, EC_NULL);
#else
    return (0 == sem_post(m_hSemaphore));
#endif
}

EC_BOOL ECSemaphore::WaitSIGNAL(EC_U32 nTimeout)
{
#ifdef EC_OS_Win32
    return WaitForSingleObject(m_hSemaphore, nTimeout);
#else
    return (0 == sem_wait(m_hSemaphore));
#endif
}
