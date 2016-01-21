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
* LibraryLoader.h
* This file for dll loader define and encapsulation.
* Eamil:  epengao@126.com
* Author: Peter Gao
* --------------------------------------------------------------------
*/

#ifndef LIBRARY_LOADER_H
#define LIBRARY_LOADER_H

#include "ECType.h"

#ifdef EC_OS_Win32
#include <windows.h>
#elif defined _LINUX
#include <Linux.h>???
#endif

class LibraryLoader
{
public:
    static EC_HANDLE   LoadDLL(EC_PCHAR pDllPath);
    static EC_VOID     FreeDLL(EC_HANDLE pDLLHandle);
    static EC_FUNENTRY GetDLLFunAddress(EC_HANDLE hDllHandle, EC_PCHAR pFunName);

private:
    LibraryLoader();
};

#endif /* LIBRARY_LOADER_H */