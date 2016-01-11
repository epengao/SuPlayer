/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * MediaClock.h
 * This file Define a clock, for media system get/set time that can be
 * used to sync audio/vido stream.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef MEDIA_CLOCK_H
#define MEDIA_CLOCK_H

#include "ECType.h"

#define TimeStamp EC_S64
#define TIME_UNIT 1000

typedef enum
{
    MediaClock_Status_Running,
    MediaClock_Status_Pause,
    MediaClock_Status_Stoped,
} MediaClock_Status;

class ClockPort;
class MediaClock
{
public:
    MediaClock();
    ~MediaClock();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    ClockPort* GetClockPort();
    TimeStamp GetClockTime();
    EC_VOID UpdateClockTime(TimeStamp nTime);
    EC_VOID ClockTimeGoForward(TimeStamp nTime);

private:
    ClockPort*        m_pPort;
    TimeStamp         m_nTime;
    TimeStamp         m_nLastUpdate;
    MediaClock_Status m_nStatu;
};

#endif /* MEDIA_CLOCK_H */
