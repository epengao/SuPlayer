/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is in the private protected, for furthe develop. 
* 
* Project:  Programming Change Destiny < PCD >
* 
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
