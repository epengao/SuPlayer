SuPlayer [Super Player]. --- ËÙ²¥

There are two projects in this product.

1 MediaEngine
================
    MediaEngine implemented base on ffmpeg as its dumxer and audio&video decoder, base on 
SDL as its video output. Base on MediaEngine SDK you can develop media player with your own UI. 
Now the SDK interfaces are very simple for study and use.

MediaEngine SDK export: [MediaEngine.h, MediaEngine.dll]

Compile:
[Win32 platform]
MediaEngine win32 VistualStudio porject file at [SuPlayer]/MediaEngine/Project/Win/MediaEngine.sln.
After build finished SDK files will be exported to [SuPlayer]/MediaEngine/Project/Win/SDK_Export folder.
[iOS platform]
Modify [SuPlayer]/MediaEngine/MediaBase/Base/Include/ECPrefDef.h
line:36  
#define EC_OS_Win32 1 ---->  #define EC_OS_iOS 1

2 SuPlayer
================
    SuPlayer is a media player implemented base on MediaEngine. You can take it as sample of MediaEngine SDK.
SuPlayer has a classic and very simple UI.

Compile:
[Win32 platform]
SuPlayer win32 VistualStudio porject file at [SuPlayer]/PlayerApp/Win/SuPlayer/project/SuPlayer.sln.
After build finished SuPlayer.exe file will be exported to [SuPlayer]/PlayerApp/Win/SuPlayer/project/Porduct folder.
[iOS platform]
Modify [SuPlayer]/MediaEngine/MediaBase/Base/Include/ECPrefDef.h
line:36  
#define EC_OS_Win32 1 ---->  #define EC_OS_iOS 1