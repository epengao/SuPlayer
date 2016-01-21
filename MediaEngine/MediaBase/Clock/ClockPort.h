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