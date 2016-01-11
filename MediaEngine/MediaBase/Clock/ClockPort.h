/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ClockPort.h
 * This file define a Port, for other moduels get clock time. 
 * We can add other methods to this class to extend the Port.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef CLOCK_PORT_H
#define CLOCK_PORT_H


#include "ECType.h"
#include "MediaClock.h"

class ClockPort
{
public:
    ClockPort(MediaClock* pOwner);
    ~ClockPort();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    TimeStamp GetClockTime();
    EC_VOID UpdateClockTime(TimeStamp nTime);
    EC_VOID ClockTimeGoForward(TimeStamp nTime);

private:
    MediaClock*    m_pOwner;
};

#endif /* CLOCK_PORT_H */