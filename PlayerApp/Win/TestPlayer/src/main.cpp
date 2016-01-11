
#pragma once

#ifdef _DEBUG
#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include "MediaEngine.h"
#include "DllLoader.h"

#include <windows.h>
using namespace std;

#define outW 1600
#define outH 900

#define Demp_YUV_Frame 0

HWND hwnd;
MediaEngineAPI sAPI;
MediaEngHandle engHandle;

int initVideo(void *drawable)
{
    //char filepath[] = "D:/coding/Dev/ECPlayer/TestVideo/test2.mp4";
    char filepath[] = "C:/Users/Public/Videos/Sample Videos/WZZ.mp4";

    memset(&sAPI, 0, sizeof(MediaEngineAPI));
    GetMediaEngineAPI fpGetAPIEntry = NULL;
    HINSTANCE hEngDLL = (HINSTANCE)LoadDLL("MediaEngine.dll");
    fpGetAPIEntry = (GetMediaEngineAPI)GetFunctionFromDll(hEngDLL, "MediaEngineAPIsEntry");
    fpGetAPIEntry(&sAPI);

    sAPI.Init(&engHandle);
    int nRet = sAPI.OpenMedia(engHandle, filepath, (VideoScreen*)drawable);
    if (nRet != PlayerEng_Err_None)
    {
        printf("Can not open media file.\n");
        return -1;
    }

    sAPI.Play(engHandle);
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }
        break;
        case  WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_KEYDOWN:
        {
            if (wParam == VK_SPACE)
                sAPI.Pause(engHandle);
            break;
        }
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASS wndclass;
    HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 128));
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = hbrush;
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = TEXT("TetrisGameWin");

    if (!RegisterClass(&wndclass)) return FALSE;

    hwnd = CreateWindow(TEXT("TetrisGameWin"),
        TEXT("TetrisGameWin"),
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX &~WS_SIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720,
        NULL, NULL, hInstance, NULL);

    VideoScreen screen;
    screen.pScreen = hwnd;
    screen.nWidth = 1280;
    screen.nHeight = 720;
    initVideo(&screen);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);



    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


