/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding < EC >
* 
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
