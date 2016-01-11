/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECMutex.cpp
 * This file for EC ecMutex interface implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECMutex.h"


ECMutex::ECMutex()
{
#ifdef EC_OS_Win32
    m_hMutex = CreateMutex(0, false, NULL); 
#elif defined EC_OS_Linux
    pthread_mutex_init(&m_hMutex, EC_NULL);
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_mutex_init(&m_hMutex, EC_NULL);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

ECMutex::~ECMutex()
{
#ifdef EC_OS_Win32
    CloseHandle(m_hMutex);
#elif defined EC_OS_Linux
    pthread_mutex_destroy(&m_hMutex);
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_mutex_destroy(&m_hMutex);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

void ECMutex::Lock()
{
#ifdef EC_OS_Win32
    WaitForSingleObject(m_hMutex, INFINITE);
#elif defined EC_OS_Linux
    pthread_mutex_lock(&m_hMutex);
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_mutex_lock(&m_hMutex);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

void ECMutex::UnLock()
{
#ifdef EC_OS_Win32
    ReleaseMutex(m_hMutex);
#elif defined EC_OS_Linux
    pthread_mutex_unlock(&m_hMutex);
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_mutex_unlock(&m_hMutex);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

