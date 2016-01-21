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
