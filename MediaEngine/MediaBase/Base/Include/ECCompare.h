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
* ECCompare.h
*
* define a abstract class, interface for user implement a compare.
*
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_COMPARE_H
#define EC_COMPARE_H

#define EC_GREATER      1
#define EC_EQUALTO      0
#define EC_LESSTHEN    -1

template<typename T>
class ECCompare
{
public:
    virtual EC_U32 GreaterThan(T* first, T* second) = 0;
};

#endif
