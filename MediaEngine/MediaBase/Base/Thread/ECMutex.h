/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECMutex.h
 * This file for Mutex define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_MUTEX_H
#define EC_MUTEX_H

#include "ECType.h"

#ifdef EC_OS_Win32
#include <windows.h>
#elif defined EC_OS_Linux
#include <pthread.h>
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
#include <pthread.h>
#elif defined EC_OS_Android
/* TODO */
#endif


class ECMutex
{
public:
    ECMutex();
    ~ECMutex();
    EC_VOID Lock();
    EC_VOID UnLock();

private:
#ifdef EC_OS_Win32
    HANDLE              m_hMutex;
#elif defined EC_OS_Linux
    pthread_mutex_t     m_hMutex;
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_mutex_t     m_hMutex;
#elif defined EC_OS_Android
    /* TODO */
#endif
};

#endif /* EC_MUTEX_H */
