/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding < EC >
*
* ECNode.h
* This file for basic struct Node type define.
* Eamil:  epengao@126.com
* Author: Peter Gao
* Version: First initinal version.
* --------------------------------------------------------------------
*/

#ifndef EC_NODE_H
#define EC_NODE_H

#include "ECType.h"


template<typename T>
class ECNode
{
public:
    ECNode(const T data)
           :m_sData(data)
           ,m_pNext(EC_NULL) {}

public:
    T          m_sData;
    ECNode<T>* m_pNext;
};


template<typename KeyT, typename ValT>
class ECPairNode
{
public:
    ECPairNode() {}
    ECPairNode(KeyT key, ValT val)
              :m_sKey(key), m_sVal(val) {}

public:
    KeyT    m_sKey;
    ValT    m_sVal;
};

#endif /* EC_NODE_H */