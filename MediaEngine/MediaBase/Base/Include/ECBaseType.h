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
* ECBaseType.h
*
* This file for redefing all the C++ basic types.
*
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: Initial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_BASE_TYPE_H
#define EC_BASE_TYPE_H

/* Pre Compiling define */
#include "ECPrefDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* signed type */
typedef char                  _EC_CHAR;
typedef short                 _EC_SHORT;
typedef int                   _EC_S32;
typedef long                  _EC_LONG;
typedef long long             _EC_S64;
typedef float                 _EC_FLOAT;
typedef double                _EC_DOUBLE;
typedef long double           _EC_LONG_DOUBLE;
typedef wchar_t               _EC_WCHAR;
typedef const char            _EC_CONST_CHAR;
/* unsigned type */
typedef unsigned char         _EC_U8;
typedef unsigned short        _EC_U16;
typedef unsigned int          _EC_U32;
typedef unsigned long long    _EC_U64;

/* bool */
typedef bool                  _EC_BOOL;
#define _EC_FALSE             0
#define _EC_TRUE              (!_EC_FALSE)

/* pointer */
typedef void*                 _EC_POINTER;
#define _EC_NULL              0

/* max define */
#define _EC_U8_MAX            0xFF
#define _EC_U16_MAX           0xFFFF
#define _EC_U32_MAX           0xFFFFFFFF
#define _EC_U64_MAX           0xFFFFFFFFFFFFFFFF

/* debug break */
#define _EC_DEBUG_BREAK       (__asm int 3);

#ifdef __cplusplus
}
#endif

#endif /* EC_BASE_TYPE_H */
