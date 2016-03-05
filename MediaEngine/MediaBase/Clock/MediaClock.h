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
    TimeStamp         m_nLastSet;
    TimeStamp         m_nLastUpdate;
    MediaClock_Status m_nStatu;
};

#endif /* MEDIA_CLOCK_H */
