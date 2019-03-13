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

#define MAINWND_WIDTH 800
#define MAINWND_HEIGHT 480

#define IDC_BUTTON_SYS 101
#define IDC_BUTTON_QUERY 102
#define IDC_BUTTON_HISTORY 103
#define IDC_BUTTON_PARAM 104
#define IDC_BUTTON_STATE 105
#define IDC_BUTTON_INFO 106

static BITMAP bmp_bkgnd;
static BITMAP bmp_sys;
static BITMAP bmp_query;
static BITMAP bmp_history;
static BITMAP bmp_param;
static BITMAP bmp_state;
static BITMAP bmp_info;

static DLGTEMPLATE DlgMainWnd = { WS_VISIBLE, WS_EX_NONE, 0, 0, 800,  480,
                                  "",         0,          0, 6, NULL, 0 };

static CTRLDATA MainWndControls[] = {
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 110, 80, 140, 140,
      IDC_BUTTON_SYS, "", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 324, 80, 140, 140,
      IDC_BUTTON_QUERY, "", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 540, 80, 140, 140,
      IDC_BUTTON_HISTORY, "", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 110, 250, 140, 140,
      IDC_BUTTON_PARAM, "", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 324, 250, 140, 140,
      IDC_BUTTON_STATE, "", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON, 540, 250, 140, 140,
      IDC_BUTTON_INFO, "", 0, WS_EX_TRANSPARENT },
};

/* 加载主界面图片 */
static BOOL LoadMainWndBmp(void)
{
    UnloadBitmap(&bmp_bkgnd);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_bkgnd, "/home/root/res/popt.jpg")) {
        printf("can not find backgroud bmp\n");
        return FALSE;
    }

    UnloadBitmap(&bmp_sys);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_sys,
                           "/home/root/res/sysQuery.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }

    UnloadBitmap(&bmp_query);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_query,
                           "/home/root/res/DataQuery.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }

    UnloadBitmap(&bmp_history);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_history,
                           "/home/root/res/historyQuery.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }
    UnloadBitmap(&bmp_param);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_param,
                           "/home/root/res/sysparam.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }
    UnloadBitmap(&bmp_state);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_state,
                           "/home/root/res/sysState.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }
    UnloadBitmap(&bmp_info);
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_info,
                           "/home/root/res/sysInfo.jpg")) {
        printf("can not find sys bmp\n");
        return FALSE;
    }
    return TRUE;
}

/* 缷载主界面图片 */
static void UnloadMainWndBmp(void)
{
    UnloadBitmap(&bmp_bkgnd);
    UnloadBitmap(&bmp_sys);
    UnloadBitmap(&bmp_history);
    UnloadBitmap(&bmp_query);
    UnloadBitmap(&bmp_param);
    UnloadBitmap(&bmp_state);
    UnloadBitmap(&bmp_info);
}

/* 设置背景图片 */
static LRESULT BmpBKGND(HWND hMainWnd)
{
    HDC hdc = GetDC(hMainWnd);
    FillBoxWithBitmap(hdc, 0, 0, MAINWND_WIDTH, MAINWND_HEIGHT, &bmp_bkgnd);
    ReleaseDC(hdc);
    return 0;
}

/* 设置控件图片 */
static void BmpControls(HWND hMainWnd)
{
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_SYS), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_sys);
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_QUERY), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_query);
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_HISTORY), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_history);
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_PARAM), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_param);
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_STATE), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_state);
    SendMessage(GetDlgItem(hMainWnd, IDC_BUTTON_INFO), BM_SETIMAGE,
                BM_IMAGE_BITMAP, (LPARAM)&bmp_info);
}

/* 处理控件按钮 */
static void ShowControls(HWND hMainWnd, UINT idc_button)
{
    switch (idc_button) {
    case IDC_BUTTON_INFO: {
        ShowWindow(hMainWnd, SW_HIDE);
        break;
    }
    default:
        break;
    }
}

static LRESULT MainWndProc(HWND hMainWnd, UINT message, WPARAM wParam,
                           LPARAM lParam)
{
    HDC hdc;

    switch (message) {
    case MSG_INITDIALOG: {
        LoadMainWndBmp();
        BmpBKGND(hMainWnd);
        BmpControls(hMainWnd);
        break;
    }
    case MSG_ERASEBKGND: {
        /* BmpBKGND(hMainWnd); */
        return 0;
        break;
    }
    case MSG_PAINT: {
        /* hdc = BeginPaint(hMainWnd); */
        /* if (!FillBoxWithBitmap(hdc, 0, 0, MAINWND_WIDTH, MAINWND_HEIGHT, */
        /*                        &bmp_bkgnd)) { */
        /*     printf("can not fill backgroud bmp\n"); */
        /* } */
        /* EndPaint(hMainWnd, hdc); */

        break;
    }
    case MSG_COMMAND: {
        ShowControls(hMainWnd, wParam);
        break;
    }
    case MSG_CLOSE: {
        UnloadMainWndBmp();
        break;
    }
    default:
        break;
    }

    return DefaultWindowProc(hMainWnd, message, wParam, lParam);
}

static int InitMainWinCreate(void)
{
    DlgMainWnd.controls = MainWndControls;
    return DialogBoxIndirectParam(&DlgMainWnd, HWND_DESKTOP, MainWndProc, 0);
}

/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    InitMainWinCreate();
    return 0;
}
