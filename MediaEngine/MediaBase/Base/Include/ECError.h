/* 
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ... 
* 
* Project:  Enjoyable Coding < EC >
* 
* ECError.h
* This file for define the base error code.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef EC_ERROR_H
#define EC_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

#define    EC_Err_None                   0x00000000
#define    EC_Err_DataNotExist           0x00000001
#define    EC_Err_NotImplement           0x00000002
#define    EC_Err_BadParam               0x00000003
#define    EC_Err_DataAlreadyExist       0x00000004
#define    EC_Err_FileOpenFaild          0x00000005
#define    EC_Err_OperatorFaild          0x00000006
#define    EC_Err_ContainerFull          0x00000007
#define    EC_Err_ContainerEmpty         0x00000008

#define    EC_Err_Memory_Base            0x0000F000
#define    EC_Err_Memory_Low             (EC_Err_Memory_Base|0x01)
#define    EC_Err_Memory_Overflow        (EC_Err_Memory_Base|0x02)
#define    EC_Err_Memory_NotAvailable    (EC_Err_Memory_Base|0x03)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EC_ERROR_H */
