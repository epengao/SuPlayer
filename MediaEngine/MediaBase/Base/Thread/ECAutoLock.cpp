/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECAutoLock.cpp
 * This file for Mutex auto lock/unlock implementation.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#include "ECAutoLock.h"


ECAutoLock::ECAutoLock(ECMutex *mutex)
:m_pmtxMutex(mutex)
{
    m_pmtxMutex->Lock();
}

ECAutoLock::~ECAutoLock()
{
    m_pmtxMutex->UnLock();
}
