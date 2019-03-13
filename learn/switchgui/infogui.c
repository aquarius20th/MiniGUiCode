/**
 *   \file infogui.c
 *   \brief 作info 信息的gui 界面
 *
 *  显示一些常见的数据及返回按键操作
 *
 */
#include "infogui.h"

#define IDC_BUTTON_RETURN 700

static BITMAP bmp_bkgnd;
static HWND hInfoWnd = HWND_INVALID;
static HWND hMainWnd;

static CTRLDATA InfoControls[] = {
    { CTRL_BUTTON, WS_VISIBLE | BS_PUSHBUTTON | BS_NOBORDER, 680, 10, 100, 40,
      IDC_BUTTON_RETURN, "return", 0, WS_EX_TRANSPARENT },
    { CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, 110, 80, 100, 20, IDC_STATIC,
      "lllllllll", 0, WS_EX_TRANSPARENT },
};

static DLGTEMPLATE DlgInfo = { WS_VISIBLE, WS_EX_NONE, 0, 0, 800,          480,
                               "",         0,          0, 2, InfoControls, 0 };

/* 设置背景图片 */
static LRESULT BmpBKGND(HWND hInfoWnd)
{
    HDC hdc = GetDC(hInfoWnd);
    FillBoxWithBitmap(hdc, 0, 0, 800, 480, &bmp_bkgnd);
    ReleaseDC(hdc);
    return 0;
}

/* 缷载主界面图片 */
static void UnloadMainWndBmp(void)
{
    UnloadBitmap(&bmp_bkgnd);
}

/* 加载主界面图片 */
static BOOL LoadMainWndBmp(void)
{
    UnloadMainWndBmp();
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_bkgnd,
                           "/home/root/res/01_06_sysinfo.jpg")) {
        printf("can not find backgroud bmp\n");
        return FALSE;
    }

    return TRUE;
}

/* 处理控件按钮 */
static void ReturnToMain(HWND hInfoWnd, UINT idc_button)
{
    switch (idc_button) {
    case IDC_BUTTON_RETURN: {
        ShowWindow(hInfoWnd, SW_HIDE);
        ShowWindow(hMainWnd, SW_SHOWNORMAL);
        break;
    }
    default:
        break;
    }
}

/* Info 界面消息处理 */
static LRESULT InfoGuiProc(HWND hInfoWnd, uint message, WPARAM wParam,
                           LPARAM lParam)
{
    HDC hdc;

    switch (message) {
    case MSG_INITDIALOG: {
        LoadMainWndBmp();
        BmpBKGND(hInfoWnd);
        break;
    }
    case MSG_ERASEBKGND: {
        BmpBKGND(hInfoWnd);
        return 0;
        break;
    }
    case MSG_COMMAND: {
        ReturnToMain(hInfoWnd, wParam);
        break;
    }
    case MSG_DESTROY: {
        DestroyAllControls(hInfoWnd);
        hInfoWnd = HWND_INVALID;
        return 0;
    }
    case MSG_CLOSE: {
        UnloadMainWndBmp();
        DestroyMainWindow(hInfoWnd);
        MainWindowCleanup(hInfoWnd);
        return 0;
    }
    default:
        break;
    }

    return DefaultDialogProc(hInfoWnd, message, wParam, lParam);
}

int InitInfoGui(HWND hWnd)
{
    if (hInfoWnd != HWND_INVALID) {
        ShowWindow(hInfoWnd, SW_SHOWNORMAL);
        return 0;
    }

    hMainWnd = hWnd;
    hInfoWnd = CreateMainWindowIndirect(&DlgInfo, hMainWnd, InfoGuiProc);

    if (hInfoWnd == HWND_INVALID) {
        return -1;
    }

    return 0;
}
