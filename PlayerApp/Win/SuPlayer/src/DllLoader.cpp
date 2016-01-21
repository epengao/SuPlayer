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
* DllLoader.cpp
*
* This file for dynamic library load APIs implementation
* Eamil:  epengao@126.com
* Author: Peter Gao
* --------------------------------------------------------------------
*/

#include "DllLoader.h"


HMODULE LoadDLL(char *pDllPath)
{
    HMODULE hModule = NULL;

    wchar_t pWDllPath[MAX_PATH_LEN];
    int nPathSize = strlen(pDllPath) + 1;
    memset(pWDllPath, 0, MAX_PATH_LEN);
    MultiByteToWideChar(CP_ACP, 0, pDllPath, nPathSize, pWDllPath, MAX_PATH_LEN);
    hModule = LoadLibrary(pWDllPath);

    return hModule;
}

void FreeDLL(HMODULE pDllHandle)
{
    if (pDllHandle) FreeLibrary(pDllHandle);
}

FARPROC GetFunctionFromDll(HMODULE hDllHandle, char* pFunName)
{
    if ((NULL == pFunName) ||
        (NULL == hDllHandle) )
        return NULL;

    return GetProcAddress(hDllHandle, (LPCSTR)pFunName);
}
