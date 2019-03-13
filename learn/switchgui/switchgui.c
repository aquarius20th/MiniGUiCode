/**
 *   \file switchgui.c
 *   \brief 一个界面切换的程序
 *
 *
 *
 */

#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

static const Uint16 MAINWND_WIDTH = 800;
static const Uint16 MAINWND_HEIGHT = 480;

static BITMAP bmp_bkgnd;

/* 加载主界面图片 */
static BOOL LoadMainWndBmp( void )
{
	UnloadBitmap(&bmp_bkgnd);
	if (LoadBitmapFromFile(HDC_SCREEN, &bmp_bkgnd, "/home/root/res/popt.jpg") <
		0) {
		printf("can not find backgroud bmp\n");
		return FALSE;
	}

	return TRUE;
}

/* 缷载主界面图片 */
static void UnloadMainWndBmp( void )
{
	UnloadBitmap(&bmp_bkgnd);
}

static LRESULT MainWndProc(HWND hMainWnd, UINT message, WPARAM wParam,
                           LPARAM lParam)
{
	HDC hdc;

    switch (message) {
    case MSG_CREATE: {
		LoadMainWndBmp();
        break;
    }
	case MSG_PAINT: {
		hdc = BeginPaint( hMainWnd );
		if (!FillBoxWithBitmap(hdc, 0, 0, MAINWND_WIDTH, MAINWND_HEIGHT, &bmp_bkgnd)) {
            printf("can not fill backgroud bmp\n");
		}
		EndPaint(hMainWnd, hdc);

		break;
	}
    case MSG_CLOSE: {
		printf( "MSG_CLOSE\n");
        break;
    }
    default:
        break;
    }

    return DefaultWindowProc(hMainWnd, message, wParam, lParam);
}

void static InitMainWinCreate(PMAINWINCREATE pInfo)
{
    pInfo->dwStyle = WS_VISIBLE;
    pInfo->dwExStyle = WS_EX_NONE;
    pInfo->spCaption = "";
    pInfo->hMenu = 0;
    pInfo->hCursor = GetSystemCursor(0);
    pInfo->hIcon = 0;
    pInfo->MainWindowProc = MainWndProc; /* 主界面处理函数 */
    pInfo->lx = 0;
    pInfo->ty = 0;
    pInfo->rx = MAINWND_WIDTH;
    pInfo->by = MAINWND_HEIGHT;
    pInfo->iBkColor = COLOR_invalid;
    pInfo->dwAddData = 0;
    pInfo->dwReserved = 0;
    pInfo->hHosting = HWND_DESKTOP;
}

/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    /* 初始化创建信息 */
    InitMainWinCreate(&CreateInfo);

    /* 创建主窗口 */
    hMainWnd = CreateMainWindow(&CreateInfo);
    if (HWND_INVALID == hMainWnd)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    /* 消息循环 */
    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}
