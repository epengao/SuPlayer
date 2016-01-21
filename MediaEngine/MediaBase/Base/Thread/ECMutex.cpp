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

