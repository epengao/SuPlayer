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
* VideoDecPort.h
* This file define a Port, for other moduels get uncompressed data,
* [AudioPCM].
* We can add other methods to this class to extend the Port.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef VIDEO_DEC_PORT_H
#define VIDEO_DEC_PORT_H


#include "ECType.h"
#include "VideoDec.h"
#include "VideoDecoder.h"

class VideoDecPort
{
public:
    VideoDecPort(VideoDecoder* pOwner);
    ~VideoDecPort();
    EC_U32 GetVideoFrame(VideoFrame** ppFrame);
    EC_VOID ReturnVideoFrame(VideoFrame* pFrame);

private:
    VideoDecoder*    m_pOwner;
};

#endif /* VIDEO_DEC_PORT_H */