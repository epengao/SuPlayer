/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is in the private protected, for furthe develop. 
* 
* Project:  Programming Change Destiny < PCD >
* 
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