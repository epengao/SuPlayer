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
* MediaEngineWap.h
* This file define a encapsulation for SuPlayer low layer media support.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef MEDIA_ENGINE_H
#define MEDIA_ENGINE_H

#include "MediaEngine.h"

class MediaEngine
{
public:
    MediaEngine(void *pDrawable,
                unsigned int nVideoWndWidth,
                unsigned int nVideoWndHight);
    ~MediaEngine();
    int  OpenMedia(char *pMediaPath);
    void Play();
    void Pause();
    void Seek(unsigned int nPos);
    void Stop();
    bool HasVideo();
    bool IsPlaying();
    bool HasPlayMedia();
    void GetMediaInfo(MediaInfo *pMediaInfo);
    void SetMediaNotify(MediaEngineNotify *pNotify);
    unsigned int GetPlayPosition();
    unsigned int GetMediaDuration();
    void UpdateVideoScreen(void *pDrawable, unsigned int nWidth, unsigned int nHeight);

private:
    void VideoScreenSizeAlign();
private:
    MediaEngineAPI    m_sMediaAPI;
    MediaEngineHandle m_hMediaHandle;
    VideoScreen       m_sVideoScreen;
};

#endif /* MEDIA_ENGINE_H */
