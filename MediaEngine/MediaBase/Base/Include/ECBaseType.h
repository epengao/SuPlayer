/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve.
* 
* Project:  Enjoyable Coder < EC >
* 
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
