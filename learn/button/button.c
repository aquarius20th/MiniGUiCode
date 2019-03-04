/*******************************************************************************
 * 文件名:button.c
 * 文件描述:MiniGui Button
 * 创建日期:2019/03/04 13:20:16
 * 版本：Ver1.0
 *
 * Copyright  2018 - 2018 mengqp.
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
#include <minigui/control.h>

static PLOGFONT gb2312_font;

#define  IDC_BUTTON              102               /* IDC_BUTTON */

static long HelloWinProc (HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message) {
        case MSG_PAINT:
            hdc = BeginPaint (hWnd);
            TextOut (hdc, 0, 0, "你好");
            EndPaint (hWnd, hdc);
            return 0;
        case MSG_CLOSE:
            DestroyLogFont(gb2312_font);
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
    }
    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

/*------------------------------------------------------------------------------
 * 函数名:InitMainWindow
 * 功能描述:定义主窗口
 * 参数:void
 * 被调用:MiniGUIMain
 * 返回值:HWND
 ------------------------------------------------------------------------------*/
static HWND InitMainWindow( void )
{
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER, "helloworld", 0, 0 );
#endif // _MGRM_PROCESSES

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    /* CreateInfo.dwStyle = WS_VISIBLE ; */
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "Button Test";

    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor (0);
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

    return hMainWnd;
}   /*-------- end InitMainWindow -------- */

/*------------------------------------------------------------------------------
 * 函数名:InitMainWindowButton
 * 功能描述:创建主窗口按钮
 * 参数:void
 * 被调用:
 * 返回值:static int
 ------------------------------------------------------------------------------*/
static int InitMainWindowButton( HWND hMainWnd )
{
    CreateWindow (CTRL_BUTTON,
                  "系统图",
                  WS_CHILD | BS_PUSHBUTTON | BS_CHECKED | WS_VISIBLE,
                  IDC_BUTTON,
                  30, 50, 120, 120, hMainWnd, 0);

    return 0;
}   /*-------- end InitMainWindowButton -------- */

/*------------------------------------------------------------------------------
 * 函数名:MiniGUIMain
 * 功能描述:程序入口
 * 参数:int argc
 * 参数:char const *argv[]
 * 被调用:
 * 返回值:int
 ------------------------------------------------------------------------------*/
int MiniGUIMain(int argc , char const *argv[] )
{
    MSG Msg;
    HWND hMainWnd;

    /* 定义主窗口 */
    hMainWnd = InitMainWindow( );
    if (hMainWnd == HWND_INVALID)
    {
        return -1;
    }

    /* 创建主窗口按钮 */
    InitMainWindowButton( hMainWnd );

    /* 显示主界面 */
    ShowWindow (hMainWnd, SW_SHOWNORMAL);
    /* 主界面消息 */
    while (GetMessage (&Msg, hMainWnd))
    {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }

    /* 清理界面 */
    MainWindowThreadCleanup (hMainWnd);

    return 0;
}   /*-------- end MiniGUIMain -------- */
