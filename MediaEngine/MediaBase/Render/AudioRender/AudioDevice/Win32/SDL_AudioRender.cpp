/*
* ---------------------------------------------------------------------
* Copyright (c) 2014~2016 All Right Reserved
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
*
* SDL_AudioRender.h
* This file is SDL_AudioRender class implementation
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#include "ECMemOP.h"
#include "ECAutoLock.h"
#include "SDL_AudioRender.h"
extern "C"
{
#include "libavformat/avformat.h"
};


SDL_AudioRender::SDL_AudioRender()
:m_bStoped(EC_FALSE)
,m_pPCMBufPos(EC_NULL)
,m_pPCMBuffer(EC_NULL)
,m_nPCMBufferSize(0)
,m_nSDLWantSize(0)
,m_nCurrPCMDataSize(0)
,m_semFullBufSIGNAL(0,1)
,m_semEmptyBufSIGNAL(0,1)
{
    SDL_memset(&m_sAudioContext, 0, sizeof(m_sAudioContext));
}

SDL_AudioRender::~SDL_AudioRender()
{
}

EC_U32 SDL_AudioRender::Init(MediaCtxInfo* pMediaInfo, AudioPCMBuffer *pFirstFrame)
{
    if (EC_NULL == pMediaInfo)
        return EC_Err_BadParam;

    m_sAudioContext.freq = pMediaInfo->m_nSampleRate;
    m_sAudioContext.silence = 0;
    m_sAudioContext.channels = 2; /* [Left & Right] */
    m_sAudioContext.samples = ((AVFrame*)pFirstFrame)->nb_samples;
    m_sAudioContext.format = AUDIO_S16SYS;
    m_sAudioContext.userdata = this;
    m_sAudioContext.callback = PlaySoundCallback;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        return Audio_Render_Err_InitFail;
    if (SDL_OpenAudio(&m_sAudioContext, NULL) < 0)
        return Audio_Render_Err_InitFail;

    return Audio_Render_Err_None;
}

EC_VOID SDL_AudioRender::Uninit()
{
    if (m_pPCMBuffer)
    {
        av_free(m_pPCMBuffer);
    }
    m_nSDLWantSize = 0;
    m_nCurrPCMDataSize = 0;
    m_pPCMBuffer = EC_NULL;
    m_pPCMBufPos = EC_NULL;
}

EC_VOID SDL_AudioRender::Run()
{
    SDL_PauseAudio(0);
}

EC_VOID SDL_AudioRender::Pause()
{
    SDL_PauseAudio(1);
}

EC_VOID SDL_AudioRender::Stop()
{
    if (m_bStoped) return;
    m_bStoped = EC_TRUE;
    m_semFullBufSIGNAL.SendSIGNAL();
    m_semEmptyBufSIGNAL.SendSIGNAL();
    SDL_CloseAudio();
    //SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

EC_VOID SDL_AudioRender::Flush()
{
    SDL_PauseAudio(1);
    m_nSDLWantSize = 0;
    m_nCurrPCMDataSize = 0;
    m_pPCMBufPos = m_pPCMBuffer;
    ecMemSet(m_pPCMBuffer, 0, m_nPCMBufferSize);
}

EC_VOID SDL_AudioRender::SendPCMData(AudioPCMBuffer *pBuffer, EC_U32 nSize)
{
    if (pBuffer && (nSize > 0))
    {
        ECAutoLock Lock(&m_mtxPCMBuffer);
        if ((nSize + m_nCurrPCMDataSize) > m_nPCMBufferSize)
        {
            uint8_t* pBuf = (uint8_t*)av_malloc(nSize + m_nCurrPCMDataSize);
            ecMemCopy(pBuf, m_pPCMBufPos, m_nCurrPCMDataSize);
            ecMemCopy(pBuf + m_nCurrPCMDataSize, pBuffer, nSize);
            if (m_pPCMBuffer) av_free(m_pPCMBuffer);
            m_pPCMBuffer = pBuf;
            m_nPCMBufferSize = nSize + m_nCurrPCMDataSize;
        }
        else
        {
            ecMemCopy(m_pPCMBuffer, m_pPCMBufPos, m_nCurrPCMDataSize);
            ecMemCopy(m_pPCMBuffer + m_nCurrPCMDataSize, pBuffer, nSize);
        }

        m_pPCMBufPos = m_pPCMBuffer;
        m_nCurrPCMDataSize = m_nCurrPCMDataSize + nSize;
    }
    if (m_bStoped) return;
    if (m_nCurrPCMDataSize >= m_nSDLWantSize)
    {
        m_semFullBufSIGNAL.SendSIGNAL();
        m_semEmptyBufSIGNAL.WaitSIGNAL();
    }
}

EC_VOID SDL_AudioRender::PlaySoundCallback(EC_VOID *pUserData, Uint8 *pStream, EC_S32 nLen )
{
    SDL_AudioRender *pSelf = (SDL_AudioRender*)pUserData;
    if (pSelf->m_bStoped) return;

    EC_BOOL bNeedWait = EC_FALSE;
    pSelf->m_nSDLWantSize = nLen;

    pSelf->m_semFullBufSIGNAL.WaitSIGNAL();
    {
        ECAutoLock Lock(&pSelf->m_mtxPCMBuffer);
        SDL_memset(pStream, 0, nLen);
        SDL_MixAudio(pStream, pSelf->m_pPCMBufPos, nLen, SDL_MIX_MAXVOLUME);
        pSelf->m_pPCMBufPos = pSelf->m_pPCMBufPos + nLen;
        pSelf->m_nCurrPCMDataSize = pSelf->m_nCurrPCMDataSize - nLen;
    }

    if (pSelf->m_nCurrPCMDataSize < nLen)
        pSelf->m_semEmptyBufSIGNAL.SendSIGNAL();
    else
        pSelf->m_semFullBufSIGNAL.SendSIGNAL();
}
