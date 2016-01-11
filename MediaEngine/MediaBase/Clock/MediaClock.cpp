/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* MediaClock.h
* This file for MediaClock class implementation
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECOSUtil.h"
#include "ClockPort.h"
#include "MediaClock.h"

MediaClock::MediaClock()
:m_pPort(EC_NULL)
,m_nTime(0)
,m_nLastUpdate(0)
,m_nStatu(MediaClock_Status_Stoped)
{
    m_pPort = new ClockPort(this);
}

MediaClock::~MediaClock()
{
    if (m_pPort) delete m_pPort;
}

EC_VOID MediaClock::Run()
{
    m_nLastUpdate = ecGetSystemTime();
    m_nStatu = MediaClock_Status_Running;
}

EC_VOID MediaClock::Pause()
{
    m_nTime = GetClockTime();
    m_nStatu = MediaClock_Status_Pause;
}

EC_VOID MediaClock::Stop()
{
    m_nTime = 0;
    m_nLastUpdate = 0;
    m_nStatu = MediaClock_Status_Stoped;
}

ClockPort* MediaClock::GetClockPort()
{
    return m_pPort;
}

TimeStamp MediaClock::GetClockTime()
{
    TimeStamp nTime = m_nTime;
    if (MediaClock_Status_Running == m_nStatu)
    {
        TimeStamp nCurrSysTime = ecGetSystemTime();
        TimeStamp nTimePassed = nCurrSysTime - m_nLastUpdate;
        nTime = m_nTime + nTimePassed;
    }
    return nTime;
}

EC_VOID MediaClock::UpdateClockTime(TimeStamp nTime)
{
    m_nTime = nTime;
    m_nLastUpdate = ecGetSystemTime();
}

EC_VOID MediaClock::ClockTimeGoForward(TimeStamp nTime)
{
    m_nTime = m_nTime + nTime;
}
