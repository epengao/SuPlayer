/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * SDL_AudioRender.h
 * Here we define a class to Package the SDL render APIs, set all these
 * APIs as a class, and this will be used in audioRender class.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef SDL_AUDIO_RENDER_H
#define SDL_AUDIO_RENDER_H

#include "ECSemaphore.h"
#include "AudioRenderDeviceI.h"

extern "C"
{
#include "sdl/SDL.h"
};

class SDL_AudioRender : public AudioRenderDeviceI
{
public:
    SDL_AudioRender();
    ~SDL_AudioRender();
public:
    EC_U32 Init(MediaCtxInfo* pMediaInfo, AudioPCMBuffer *pFirstFrame);
    EC_VOID Uninit();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    EC_VOID Flush();
    EC_VOID SendPCMData(AudioPCMBuffer *pBuffer, EC_U32 nSize);
private:
    static EC_VOID PlaySoundCallback(EC_VOID *pUserData, Uint8 *pStream, EC_S32 nLen);
private:
    EC_BOOL       m_bStoped;
    uint8_t*      m_pPCMBufPos;
    uint8_t*      m_pPCMBuffer;
    EC_U32        m_nPCMBufferSize;
    EC_U32        m_nSDLWantSize;
    EC_U32        m_nCurrPCMDataSize;

    ECMutex       m_mtxPCMBuffer;
    ECSemaphore   m_semFullBufSIGNAL;
    ECSemaphore   m_semEmptyBufSIGNAL;
    SDL_AudioSpec m_sAudioContext;
};

#endif /* SDL_VIDEO_RENDER_H */