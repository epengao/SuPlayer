/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding < EC >
 *
 * ECCompare.h
 *
 * define a abstract class, interface for user implement a compare.
 *
 * Eamil:  epengao@126.com
 * Author: Peter Gao
 * Version: First initinal version.
 * --------------------------------------------------------------------
 */

#ifndef EC_COMPARE_H
#define EC_COMPARE_H

#define EC_GREATER      1
#define EC_EQUALTO      0
#define EC_LESSTHEN    -1

template<typename T>
class ECCompare
{
public:
    virtual EC_U32 GreaterThan(T* first, T* second) = 0;
};

#endif
