/*******************************************************************************
 * 文件名:main.c
 * 文件描述:hello world
 * 创建日期:2019/02/28 10:17:54
 * 版本：Ver1.0
 *
 * Copyright © 2018 - 2018 mengqp.
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/
#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

static long HelloWinProc (HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message) {
        case MSG_PAINT:
            hdc = BeginPaint (hWnd);
            TextOut (hdc, 60, 60, "wqi!");
            EndPaint (hWnd, hdc);
            return 0;
        case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
    }
    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

/*------------------------------------------------------------------------------
 * 函数名: MiniGuiMain
 * 功能描述: 程序起始入口
 ------------------------------------------------------------------------------*/
int MiniGUIMain(int argc, char const *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER, "helloworld", 0, 0 );
#endif // _MGRM_PROCESSES

    /* CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION; */
    CreateInfo.dwStyle = WS_VISIBLE ;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "helloworld";

    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor (2);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 800;
    CreateInfo.by = 480;
    CreateInfo.iBkColor = COLOR_darkblue;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;
    hMainWnd = CreateMainWindow (&CreateInfo);
    if (hMainWnd == HWND_INVALID)
    {
        return -1;
    }
    ShowWindow (hMainWnd, SW_SHOWNORMAL);
    while (GetMessage (&Msg, hMainWnd))
    {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }
    MainWindowThreadCleanup (hMainWnd);

    return 0;
}
