/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECSemaphore.h
 * This file for ecSemaphore define and encapsulation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_SEMAPHORE_H
#define EC_SEMAPHORE_H

#include "ECType.h"

#ifdef EC_OS_Win32
#include <windows.h>
#else
#include <semaphore.h>
#endif


class ECSemaphore
{
public:
    ECSemaphore(EC_U32 nInitSig = 0, EC_U32 nMaxSig = EC_U16_MAX);
    ~ECSemaphore();

    EC_BOOL SendSIGNAL();
    EC_BOOL WaitSIGNAL(EC_U32 nTimeout = EC_U32_MAX);

private:
#ifdef EC_OS_Win32
    HANDLE         m_hSemaphore;
#else
    sem_t*         m_hSemaphore;
    EC_PCHAR       m_pSemaphoreName;
#endif
};

#endif /* EC_SEMAPHORE_H */