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
* ECDllLoader.h
* This file for dll loader APIs define.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_DLL_LOADER_H
#define EC_DLL_LOADER_H

#include "ECType.h"

#ifdef EC_OS_Win32
#include <windows.h>
#elif defined EC_OS_Linux
#include <unistd.h>
#elif defined EC_OS_MacOS
/* TODO */
#elif defined EC_OS_iOS
/* TODO */
#elif defined EC_OS_Android
/* TODO */
#endif

#ifdef __cplusplus
extern "C" {
#endif

EC_HANDLE   ecLoadDLL(EC_PCHAR pDllPath);
EC_VOID     ecFreeDLL(EC_HANDLE pDLLHandle);
EC_FUNENTRY ecGetDLLFunAddress(EC_HANDLE hDllHandle, EC_PCHAR pFunName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* EC_LIBRARY_LOADER_H */