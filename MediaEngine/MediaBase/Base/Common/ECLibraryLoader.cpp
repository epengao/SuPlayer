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
* LibraryLoader.cpp
* This file for dynamic library loader implementation
* Eamil:  epengao@126.com
* Author: Peter Gao
* --------------------------------------------------------------------
*/

#include "ECLibraryLoader.h"

EC_HANDLE LibraryLoader::LoadDLL(EC_PCHAR pDllPath)
{
    EC_HANDLE pRet = EC_NULL;
#ifdef _WIN32
    EC_WCHAR pWDllPath[1024];  
    EC_U32 nPathSize = strlen(pDllPath) + 1;
    memset(pWDllPath, 0, 1024);  
    MultiByteToWideChar(CP_ACP, 0, pDllPath, nPathSize, pWDllPath, 1024);  

    pRet = LoadLibrary( pWDllPath );
#elif defined _LINUX
    pRet = XXX; /* TODO: implement linux platform dll loader*/
#endif
    return pRet;
}

EC_FUNENTRY LibraryLoader::GetDLLFunAddress(EC_HANDLE hDllHandle, EC_PCHAR pFunName)
{
    if (EC_NULL == hDllHandle)
        return EC_NULL;

    EC_HANDLE pRet = EC_NULL;
#ifdef _WIN32
    pRet = (EC_FUNENTRY)GetProcAddress((HMODULE)hDllHandle, (LPCSTR)pFunName);
#elif defined _LINUX
    pRet = XXX; /* TODO: implement linux platform fun address get*/
#endif
    return pRet;
}

void LibraryLoader::FreeDLL(EC_HANDLE pDLLHandle)
{
    if(EC_NULL == pDLLHandle)
        return;
#ifdef _WIN32
    FreeLibrary((HMODULE)pDLLHandle);
#elif defined _LINUX
    /* TODO: linux platform implementation */
#endif
}
