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
* ECSignal.cpp
* This file for ECSignal interface implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECSignal.h"


ECSignal::ECSignal()
{
#ifdef EC_OS_Win32
    m_hSemaphore = CreateSemaphore(EC_NULL, 0, 1, EC_NULL);
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    m_Cond = PTHREAD_COND_INITIALIZER;
    m_Mutex = PTHREAD_MUTEX_INITIALIZER;
#elif defined EC_OS_Android
    /* TODO */
#endif
}

ECSignal::~ECSignal()
{
#ifdef EC_OS_Win32
    CloseHandle(m_hSemaphore);
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    /* TODO */
#elif defined EC_OS_Android
    /* TODO */
#endif
}

void ECSignal::Wait()
{
#ifdef EC_OS_Win32
    WaitForSingleObject(m_hSemaphore, INFINITE);
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_cond_wait(&m_Cond, &m_Mutex);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

void ECSignal::Send()
{
#ifdef EC_OS_Win32
    ReleaseSemaphore(m_hSemaphore, 1, EC_NULL);
#elif defined EC_OS_Linux
    /* TODO */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    pthread_cond_signal(&m_Cond);
#elif defined EC_OS_Android
    /* TODO */
#endif
}

