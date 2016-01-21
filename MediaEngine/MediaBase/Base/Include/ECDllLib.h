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
* ECDllLib.h
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_DLL_LIB_H
#define EC_DLL_LIB_H

#include "ECPrefDef.h"

#ifdef EC_OS_Win32
#include <windows.h>
#else
#include <Linux.h> /* TODO */
#endif


#ifdef __cplusplus
#define EC_EXPORT extern "C" __declspec (dllexport)
#else
#define EC_EXPORT            __declspec (dllexport)
#endif

#ifdef EC_OS_Win32
#define  EC_ExAPI    WINAPI
#else
#define  EC_ExAPI    /* Linux API or iOS API*/
#endif

#endif /* EC_DLL_LIB_H */