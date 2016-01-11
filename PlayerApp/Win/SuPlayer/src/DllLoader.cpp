/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is in the private protected, for furthe develop. 
* 
* Project:  Programming Change Destiny < PCD >
* 
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
