/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
*
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
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

