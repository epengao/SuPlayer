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