/*******************************************************************************
 * 文件名:helloworld.c
 * 文件描述:抄自src/helloworld.c
 * 创建日期:2019/03/06 15:13:11
 * 版本：Ver1.0
 *
 * Copyright © 2018 - 2018 mengqp.
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

/* 系统库 */
#include <stdio.h>
#include <string.h>

/* MG库 */
#include <minigui/common.h>
#include <minigui/gdi.h>
#include <minigui/minigui.h>
#include <minigui/window.h>

static char welcome_text[ 512 ];
static RECT welcome_rc = { 10, 100, 600, 400 };

static char msg_text[ 256 ];
static RECT msg_rc = { 10, 100, 600, 400 };

/*------------------------------------------------------------------------------
 * 函数名:make_welcome_text
 * 功能描述:welcome
 * 参数:void
 * 被调用:
 * 返回值:static void
 ------------------------------------------------------------------------------*/
static void make_welcome_text( void )
{
    const char *format;

    SetRect( &welcome_rc, 10, 10, g_rcScr.right - 10, g_rcScr.bottom / 2 - 10 );
    SetRect( &msg_rc, 10, welcome_rc.bottom + 10, g_rcScr.right - 10, g_rcScr.bottom - 20 );

    format = "MiniGUI Version %d.%d.%d can run on this hardware board.";
    sprintf( welcome_text, format, MINIGUI_MAJOR_VERSION, MINIGUI_MINOR_VERSION, MINIGUI_MICRO_VERSION );
    strcpy( msg_text, "timer=0" );

} /*-------- end make_welcome_text -------- */
/*------------------------------------------------------------------------------
 * 函数名:HelloWinProc
 * 功能描述:主窗口消息处理函数
 * 参数:HWND hwnd 主窗口句柄
 * 参数:UINT message 主窗口消息类型
 * 参数:WPARAM wParam 主窗口消息参数
 * 参数:LPARAM lParam  主窗口消息参数
 * 被调用:
 * 返回值:static LRESULT
 ------------------------------------------------------------------------------*/
static LRESULT HelloWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC hdc;
    switch ( message )
    {
        case MSG_CREATE:  // 创建
        {
            make_welcome_text();
            SetTimer( hWnd, 100, 20 );
        }
        break;

        case MSG_TIMER:
            sprintf( msg_text, "timer=%d ms", ( PVOID )GetTickCount() );
            /* InvalidateRect (hWnd, &msg_rc, TRUE); */
            break;

        case MSG_PAINT:
            hdc = BeginPaint( hWnd );
            DrawText( hdc, welcome_text, -1, &welcome_rc, DT_LEFT | DT_WORDBREAK );
            DrawText( hdc, msg_text, -1, &msg_rc, DT_LEFT | DT_WORDBREAK );
            EndPaint( hWnd, hdc );
            return 0;

        case MSG_CLOSE:
            KillTimer( hWnd, 100 );
            DestroyMainWindow( hWnd );
            PostQuitMessage( hWnd );
            return 0;

        default:
            break;
    }

    return DefaultMainWinProc( hWnd, message, wParam, lParam );
} /*-------- end HelloWinProc -------- */

/* main */
int MiniGUIMain( int argc, const char *argv[] )
{
    MSG           Msg;
    HWND          hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle        = WS_VISIBLE;
    CreateInfo.dwExStyle      = WS_EX_NONE;
    CreateInfo.spCaption      = "hello";
    CreateInfo.hMenu          = 0;
    CreateInfo.hCursor        = GetSystemCursor( 0 );
    CreateInfo.hIcon          = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx             = 0;
    CreateInfo.ty             = 0;
    CreateInfo.rx             = g_rcScr.right;
    CreateInfo.by             = g_rcScr.bottom;
    CreateInfo.iBkColor       = COLOR_lightwhite;
    CreateInfo.dwAddData      = 0;
    CreateInfo.hHosting       = HWND_DESKTOP;

    hMainWnd = CreateMainWindow( &CreateInfo );

    if ( hMainWnd == HWND_INVALID )
        return -1;

    ShowWindow( hMainWnd, SW_SHOWNORMAL );

    while ( GetMessage( &Msg, hMainWnd ) )
    {
        TranslateMessage( &Msg );
        DispatchMessage( &Msg );
    }

    MainWindowThreadCleanup( hMainWnd );

    return 0;
}
