/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECSignal.h
 * This file for mutil thread used signal define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_SIGNAL_H
#define EC_SIGNAL_H

#include "ECMutex.h"

#ifdef EC_OS_Win32
#include <windows.h>
#elif defined EC_OS_Linux
/* TODO */
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
#include <pthread.h>
#elif defined EC_OS_Android
/* TODO */
#endif


class ECSignal
{
public:
    ECSignal();
    ~ECSignal();
    void Wait();
    void Send();

private:

#ifdef EC_OS_Win32
    HANDLE  m_hSemaphore;
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_cond_t m_Cond;
    pthread_mutex_t m_Mutex;
#elif defined EC_OS_Android
    /* TODO */
#endif
};

#endif /* EC_SIGNAL_H */
