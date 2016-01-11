/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECAutoLock.h
 * This file for Mutex auto lock/unlock define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_AUTOLOCK_H
#define EC_AUTOLOCK_H

#include "ECMutex.h"


class ECAutoLock
{
public:
    ECAutoLock(ECMutex* mutex);
    ~ECAutoLock();

private:
    ECMutex*  m_pmtxMutex;
};

#endif /* EC_AUTOLOCK_H */