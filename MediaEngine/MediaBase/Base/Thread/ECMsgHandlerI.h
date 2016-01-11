/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * ECMsgHandlerI.h
 *
 * This file for thread message handler interface.
 * Any module want to use thread to dispathch message, 
 * need to implement all the functions define here.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef EC_MSG_HANDLER_I_H
#define EC_MSG_HANDLER_I_H

#include "ECType.h"

class ECMsgHandlerI
{
public:
    virtual ~ECMsgHandlerI(){};
    virtual EC_VOID CleanMsg() = 0;
    virtual EC_U32 PushMsg(void* pMsg) = 0;
    virtual EC_U32 PopMsg(void** ppMsg) = 0;    
    virtual EC_VOID DestroyMsg(void* pMsg) = 0;
    virtual EC_VOID  DispatchMsg(void* pMsg = EC_NULL) = 0;
};

#endif /* EC_MSG_HANDLER_I_H */