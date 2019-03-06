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


#define  IDC_BUTTON              102               /* IDC_BUTTON */
#define  WIDTH                   800                             /*  */
#define  HEIGHT                  480                             /*  */
BITMAP bmp_button1;
BITMAP bmp_button2;

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
                  "按钮",
                  WS_CHILD | BS_PUSHBUTTON | BS_FLAT | BS_LEFTTEXT | WS_VISIBLE,
                  IDC_BUTTON,
                  30, 50, 120, 120, hMainWnd, 0);

    PLOGFONT buttonFont = CreateLogFont ("ttf", "simsun", "UTF-8",
                                          FONT_WEIGHT_BOOK, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
                                          FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                                          32, 0);

    SetWindowFont( GetDlgItem(hMainWnd, IDC_BUTTON), buttonFont );

    if(LoadBitmapFromFile(HDC_SCREEN, &bmp_button1, (char *)"/home/root/res/DataQuery.jpg" ))
    {
        return -1;
    }

    if(LoadBitmapFromFile(HDC_SCREEN, &bmp_button2, (char *)"/home/root/res/sg.jpg" ))
    {
        return -1;
    }
    CreateWindow (CTRL_BUTTON,
                  "背景图片",
                  WS_CHILD | BS_PUSHBUTTON | BS_BITMAP | BS_NOBORDER  | BS_NOTIFY | WS_VISIBLE,
                  IDC_BUTTON + 1,
                  180, 50, 100, 100, hMainWnd, (DWORD)&bmp_button1);

    CreateWindow (CTRL_BUTTON,
                  "Close",
                  WS_CHILD | BS_PUSHBUTTON | BS_BITMAP  | BS_NOTIFY | BS_NOBORDER | WS_VISIBLE ,
                  IDC_BUTTON + 2,
                  10, 300, 120, 80, hMainWnd, (DWORD) GetSystemBitmap (GetDlgItem(hMainWnd, IDC_BUTTON + 2), IDI_APPLICATION));
                  /* 10, 300, 60, 30, hMainWnd, (DWORD) &bmp_button1); */

    /* SetWindowFont( GetDlgItem(hMainWnd, IDC_BUTTON + 1), buttonFont ); */

    SendMessage (GetDlgItem(hMainWnd, IDC_BUTTON + 1), BM_SETSTYLE, BS_NOBORDER, 0) ;
    SendMessage (GetDlgItem(hMainWnd, IDC_BUTTON + 1), BM_SETIMAGE, BM_IMAGE_BITMAP, (LPARAM)&bmp_button1) ;
    SendMessage (GetDlgItem(hMainWnd, IDC_BUTTON + 2), BM_SETIMAGE, BM_IMAGE_BITMAP, (LPARAM)&bmp_button2) ;

    /* printf("border=%d\n", GetMessage(GetDlgItem(hMainWnd, IDC_BUTTON + 1), BM_GETSTATE, )); */
    /* SendMessage (GetDlgItem(hMainWnd, IDC_BUTTON + 2), BS_NOBORDER, 0, 0) ; */

    return 0;
}   /*-------- end InitMainWindowButton -------- */


static long HelloWinProc (HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    BITMAP bmp;
    switch (message)
    {
        case MSG_CREATE://comment
            {
                InitMainWindowButton(hWnd);
            }
            break;
        case MSG_PAINT:
            /* if(LoadBitmapFromFile(HDC_SCREEN, &bmp, (char *)"/home/root/res/popt.jpg" )) */
            /* { */
            /*     return -1; */
            /* } */


            hdc = BeginPaint(hWnd);
            /* FillBoxWithBitmap(hdc, 0, 0, WIDTH, HEIGHT, &bmp); */

            EndPaint (hWnd, hdc);


            return 0;
        case MSG_CLOSE:
            DestroyAllControls (hWnd);
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

    /* CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION; */
    CreateInfo.dwStyle = WS_VISIBLE ;
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

    SetDefaultWindowElementRenderer((char *)"flat");
    /* 定义主窗口 */
    hMainWnd = InitMainWindow( );
    if (hMainWnd == HWND_INVALID)
    {
        return -1;
    }

    /* 创建主窗口按钮 */
    /* InitMainWindowButton( hMainWnd ); */

    /* 设置背景顔色 */
    SetWindowBkColor 	( 	hMainWnd, 0xff040000 );
    SetWindowBkColor 	( 	GetDlgItem(hMainWnd, IDC_BUTTON), 0x000192d3 );
    SetWindowBkColor 	( 	GetDlgItem(hMainWnd, IDC_BUTTON + 1), 0xff040000);
    SetWindowBkColor 	( 	GetDlgItem(hMainWnd, IDC_BUTTON + 2), 0xff0192d3);

    /* WINDOW_ELEMENT_RENDERER *pSkin = GetWindowRendererFromName("skin"); */

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
