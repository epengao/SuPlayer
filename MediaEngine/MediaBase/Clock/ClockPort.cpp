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
* ClockPort.cpp
* This file for ClockPort class implementaion
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/
#include "ClockPort.h"

ClockPort::ClockPort(MediaClock* pOwner)
:m_pOwner(pOwner)
{
}

ClockPort::~ClockPort()
{
}

EC_VOID ClockPort::Run()
{
    m_pOwner->Run();
}

EC_VOID ClockPort::Pause()
{
    m_pOwner->Pause();
}

EC_VOID ClockPort::Stop()
{
    m_pOwner->Stop();
}

TimeStamp ClockPort::GetClockTime()
{
    return m_pOwner->GetClockTime();
}

EC_VOID ClockPort::UpdateClockTime(TimeStamp nTime)
{
    m_pOwner->UpdateClockTime(nTime);
}

EC_VOID ClockPort::ClockTimeGoForward(TimeStamp nTime)
{
    m_pOwner->ClockTimeGoForward(nTime);
}

