/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * DllLoader.h
 * This file for dll loader APIs define.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef DLL_LOADER_H
#define DLL_LOADER_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define    MAX_PATH_LEN    512

HMODULE LoadDLL(char *pDllPath);
void FreeDLL(HMODULE pDllHandle);
FARPROC GetFunctionFromDll(HMODULE hDllHandle, char* pFunName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* DLL_LOADER_H */