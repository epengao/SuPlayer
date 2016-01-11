/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding < EC >
*
* ECMathUtil.cpp
* This file for math util APIs implementaion.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECMathUtil.h"


#define ABS(number)              \
    do                           \
    {                            \
        if((number) < 0)         \
            return (0 - number); \
        else                     \
            return (number);     \
    } while (0)


EC_U32 ecMathUtilAbsS32(EC_S32 nNumber)
{
    ABS(nNumber);
}

EC_DOUBLE ecMathUtilAbsDouble(EC_DOUBLE nNumber)
{
    ABS(nNumber);
}
