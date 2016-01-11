/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
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
