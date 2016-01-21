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
