/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is in the private protected, for furthe develop. 
* 
* Project:  Programming Change Destiny < PCD >
* 
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
