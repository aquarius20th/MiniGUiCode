/*******************************************************************************
 * 文件名:bitblt.c
 * 文件描述:src/bitblt.c
 * 创建日期:2019/03/07 10:12:27
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
#include <minigui/gdi.h>
#include <minigui/minigui.h>
#include <minigui/window.h>

/*------------------------------------------------------------------------------
 * 函数名:BitBltWinProc
 * 功能描述:主界面处理函数
 * 参数:HWND hWnd 主句柄
 * 参数:UINT message  消息
 * 参数:WPARAM wParam
 * 参数:LPARAM lParam
 * 被调用:
 * 返回值:static LRESULT
 ------------------------------------------------------------------------------*/
static LRESULT BitbltWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC hdc;
    int x, y;

    switch ( message )
    {
        case MSG_PAINT:  // 画
        {
            hdc = BeginPaint( hWnd );
            SetBrushColor( hdc, PIXEL_green );
            FillCircle( hdc, 10, 10, 8 );
            for ( y = 0; y < 240; y += 20 )
            {
                for ( x = 0; x < 320; x += 20 )
                {
                    BitBlt( hdc, 0, 0, 20, 20, hdc, x, y, 0 );
                }
            }

            EndPaint( hWnd, hdc );
            return 0;
        }
        break;

        case MSG_CLOSE:  //comment
        {
            DestroyAllControls( hWnd );
            DestroyMainWindow( hWnd );
            PostQuitMessage( hWnd );
            return 0;
        }
        break;
        default:
            break;
    }

    return DefaultMainWinProc( hWnd, message, wParam, lParam );
} /*-------- end BitBltWinProc -------- */

int MiniGUIMain( int argc, const char *arg[] )
{
    MSG           Msg;
    HWND          hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle        = WS_VISIBLE;
    CreateInfo.dwExStyle      = WS_EX_NONE;
    CreateInfo.spCaption      = "";
    CreateInfo.hMenu          = 0;
    CreateInfo.hCursor        = GetSystemCursor( 0 );
    CreateInfo.hIcon          = 0;
    CreateInfo.MainWindowProc = BitbltWinProc;
    CreateInfo.lx             = 0;
    CreateInfo.ty             = 0;
    CreateInfo.rx             = 320;
    CreateInfo.by             = 240;
    CreateInfo.iBkColor       = COLOR_lightwhite;
    CreateInfo.dwAddData      = 0;
    CreateInfo.hHosting       = HWND_DESKTOP;

    hMainWnd = CreateMainWindow( &CreateInfo );

    if ( HWND_INVALID == hMainWnd )
    {
        return -1;
    }

    ShowWindow( hMainWnd, SW_SHOWNORMAL );

    while ( GetMessage( &Msg, hMainWnd ) )
    {
        TranslateMessage( &Msg );
        DispatchMessage( &Msg );
    }

    MainWindowThreadCleanup( hMainWnd );

    return 0;
}
