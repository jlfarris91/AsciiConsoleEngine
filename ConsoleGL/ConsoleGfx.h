#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0502
#include <windows.h>

#define WM_SETCONSOLEINFO (WM_USER+201) 
#pragma pack(push, 1) 
typedef struct _CONSOLE_INFO
{
    ULONG Length;
    COORD ScreenBufferSize;
    COORD WindowSize;
    ULONG WindowPosX;
    ULONG WindowPosY;
    COORD FontSize;
    ULONG FontFamily;
    ULONG FontWeight;
    WCHAR FaceName[32];
    ULONG CursorSize;
    ULONG FullScreen;
    ULONG QuickEdit;
    ULONG AutoPosition;
    ULONG InsertMode;
    USHORT ScreenColors;
    USHORT PopupColors;
    ULONG HistoryNoDup;
    ULONG HistoryBufferSize;
    ULONG NumberOfHistoryBuffers;
    COLORREF ColorTable[16];
    ULONG CodePage;
    HWND Hwnd;
    WCHAR ConsoleTitle[0x100];
} CONSOLE_INFO;
#pragma pack(pop) 

typedef struct CONSOLE_FONT
{
    DWORD index;
    COORD dimension;
} CONSOLE_FONT;

typedef CHAR_INFO CharInfo;
typedef WORD CharAttr;
typedef unsigned char Char;