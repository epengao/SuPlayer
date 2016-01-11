/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
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