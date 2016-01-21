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
* ECDllLoader.cpp
*
* This file for dynamic library load APIs implementation
* Eamil:  epengao@126.com
* Author: Peter Gao
* --------------------------------------------------------------------
*/

#include "ECDllLoader.h"


EC_HANDLE ecLoadDLL(EC_PCHAR pDllPath)
{
    EC_HANDLE pRet = EC_NULL;
#ifdef EC_OS_Win32
    EC_WCHAR pWDllPath[1024];
    EC_U32 nPathSize = strlen(pDllPath) + 1;
    memset(pWDllPath, 0, 1024);  
    MultiByteToWideChar(CP_ACP, 0, pDllPath, nPathSize, pWDllPath, 1024);  
    pRet = LoadLibrary( pWDllPath );
#elif defined EC_OS_Linux
    pRet = XXX; /* TODO: implement linux platform dll loader*/
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    /* TODO */
#elif defined EC_OS_Android
    /* TODO */
#endif
    return pRet;
}

EC_VOID ecFreeDLL(EC_HANDLE pDLLHandle)
{
    if(EC_NULL == pDLLHandle)
        return;

#ifdef EC_OS_Win32
    FreeLibrary((HMODULE)pDLLHandle);
#elif defined EC_OS_Linux
    /* TODO: linux platform implementation */
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    /* TODO */
#elif defined EC_OS_Android
    /* TODO */
#endif
}

EC_FUNENTRY ecGetDLLFunAddress(
    EC_HANDLE hDllHandle, EC_PCHAR pFunName)
{
    if (EC_NULL == hDllHandle)
        return EC_NULL;

    EC_HANDLE pRet = EC_NULL;
#ifdef EC_OS_Win32
    pRet = (EC_FUNENTRY)GetProcAddress((HMODULE)hDllHandle, (LPCSTR)pFunName);
#elif defined EC_OS_Linux
    pRet = XXX; /* TODO: implement linux platform fun address get*/
#elif defined EC_OS_MacOS
    /* TODO */
#elif defined EC_OS_iOS
    /* TODO */
#elif defined EC_OS_Android
    /* TODO */
#endif

    return pRet;
}
