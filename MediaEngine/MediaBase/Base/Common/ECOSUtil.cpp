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
* ECOSUtil.cpp
* This program is file for OS depends Util functions implementation.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include <time.h>
#include <stdlib.h>
#include "ECOSUtil.h"

#ifdef EC_OS_Win32
#include <windows.h>
#elif defined EC_OS_Linux
#include <unistd.h>
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
#include <unistd.h>
#include <sys/time.h>
#elif defined EC_OS_Android
/* TODO */
#endif


EC_VOID ecGetSystemDate(EC_Date *pDate)
{
#ifdef EC_OS_Win32
	/* TODO */
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

EC_VOID ecSleep(EC_U32 nTime)
{
#ifdef EC_OS_Win32
    Sleep(nTime);
#elif defined EC_OS_Linux
    sleep(nTime);
#elif defined EC_OS_MacOS
	/* TODO */
#elif defined EC_OS_iOS
    usleep(nTime*1000);
#elif defined EC_OS_Android
	/* TODO */
#endif
}

EC_VOID ecUSleep(EC_U32 nTime)
{
#ifdef EC_OS_Win32
	__int64 time1 = 0, time2 = 0, freq = 0;

	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	do {
		QueryPerformanceCounter((LARGE_INTEGER *)&time2);
	} while ((time2 - time1) < nTime*freq / 1000000);
#elif defined EC_OS_Linux
    usleep(nTime);
#elif defined EC_OS_MacOS
	/* TODO */
#elif defined EC_OS_iOS
    usleep(nTime);
#elif defined EC_OS_Android
	/* TODO */
#endif
}

EC_U32 ecGetSystemTime()
{
    EC_U32 nRet = 0;

#ifdef EC_OS_Win32
    nRet = GetTickCount();
#elif defined EC_OS_Linux
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    nRet = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#elif defined EC_OS_MacOS
	/* TODO */
#elif defined EC_OS_iOS
    timeval curTime;
    gettimeofday(&curTime, EC_NULL);
    nRet = (EC_U32)curTime.tv_sec*1000 + (EC_U32)(curTime.tv_usec/1000);
#elif defined EC_OS_Android
	/* TODO */
#endif

    return nRet;
}

EC_U32 ecGetRandNumber()
{
    srand( (EC_U32)time(NULL) );
    return (EC_U32)rand();
}

EC_U64  ecGetSystemTimeU()
{
    EC_U64 nRet = 0;

#ifdef EC_OS_Win32
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nCount;
    QueryPerformanceCounter(&nCount);
    QueryPerformanceFrequency(&nFreq);
    nRet = nCount.QuadPart * 1000000/ nFreq.QuadPart;
#elif defined EC_OS_Linux
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    nRet = (ts.tv_sec * 1000 * 1000 + ts.tv_nsec / 1000);
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    timeval curTime;
    gettimeofday(&curTime, EC_NULL);
    nRet = (EC_U32)curTime.tv_sec*1000*1000 + (EC_U32)curTime.tv_usec;
#elif defined EC_OS_Android
    /* TODO */
#endif

    return nRet;
}
