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
* ECLog.h
* This file for all log output hreader file define.
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_LOG_H
#define EC_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


/* Following is the detail log output define */
#define __EC_LOGI(format, ...)                                  \
    do                                                          \
    {                                                           \
        printf("EC_Info: %s %s %d " format "\n",                \
              __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__ );\
    } while (0)

#define __EC_LOGW(format, ...)                                  \
    do                                                          \
    {                                                           \
        printf("EC_Waring: %s %s %d " format "\n",              \
              __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__ );\
    } while (0)

#define __EC_LOGE(format, ...)                                  \
    do                                                          \
    {                                                           \
        printf("EC_Error: %s %s %d " format "\n",               \
              __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__ );\
    } while (0)


/* Following is the simple output log define */
#define __S_EC_LOGI(format, ...)                                \
    do                                                          \
    {                                                           \
    printf("Info:  " format "\n", ##__VA_ARGS__ );              \
} while (0)

#define __S_EC_LOGW(format, ...)                                \
    do                                                          \
    {                                                           \
    printf("Warring:  " format "\n", ##__VA_ARGS__ );           \
} while (0)

#define __S_EC_LOGE(format, ...)                                \
    do                                                          \
    {                                                           \
    printf("Err:  " format "\n", ##__VA_ARGS__ );               \
} while (0)

/* EC used log macro define */
#define EC_LOGI  __EC_LOGI
#define EC_LOGW  __EC_LOGW
#define EC_LOGE  __EC_LOGE

#define ecLogI    EC_LOGI
#define ecLogW    EC_LOGW
#define ecLogE    EC_LOGE

#define secLogI   __S_EC_LOGI
#define secLogW   __S_EC_LOGW
#define secLogE   __S_EC_LOGE


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* EC_LOG_H */
