/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ECDllLib.h
 * Eamil:  epengao@126.com
 * Author: Peter Gao
 * Version: First initinal version.
 * --------------------------------------------------------------------
 */

#ifndef EC_DLL_LIB_H
#define EC_DLL_LIB_H

#include "ECPrefDef.h"

#ifdef EC_OS_Win32
#include <windows.h>
#else
#include <Linux.h> /* TODO */
#endif


#ifdef __cplusplus
#define EC_EXPORT extern "C" __declspec (dllexport)
#else
#define EC_EXPORT            __declspec (dllexport)
#endif

#ifdef EC_OS_Win32
#define  EC_ExAPI    WINAPI
#else
#define  EC_ExAPI    /* Linux API or iOS API*/
#endif

#endif /* EC_DLL_LIB_H */