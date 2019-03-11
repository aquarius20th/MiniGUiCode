/**
 *   \file src/capture.c
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDC_MYBUTTON 100

/* button 的处理函数 */
static LRESULT MybuttonWindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam)
{
    HDC hdc;
    static int status = 0;

    switch (message) {
    case MSG_LBUTTONDOWN: {
        status = 1;
        SetCapture(hWnd);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case MSG_LBUTTONUP: {
        if (GetCapture() != hWnd)
            break;
        status = 0;
        ReleaseCapture();
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case MSG_PAINT: {
        hdc = BeginPaint(hWnd);
        if (status) {
            SetBkMode(hdc, BM_TRANSPARENT);
            TextOut(hdc, 10, 0, "pressed");
        }
        EndPaint(hWnd, hdc);
        return 0;
        break;
    }

    case MSG_DESTROY: {
        return 0;
        break;
    }

    default:
        break;
    }

    return DefaultControlProc(hWnd, message, wParam, lParam);
}

/* 注册button */
BOOL RegisterMybutton(void)
{
    WNDCLASS WndClass;
    WndClass.spClassName = "mybutton";
    WndClass.dwStyle = 0;
    WndClass.dwExStyle = 0;
    WndClass.hCursor = GetSystemCursor(0);
    WndClass.iBkColor = PIXEL_lightgray;
    WndClass.WinProc = MybuttonWindowProc;

    return RegisterWindowClass(&WndClass);
}

/**
 *  \brief main window proc
 *
 *  Detailed description
 *
 *  \param param
 *  \return return type
 */
static LRESULT CaptureWinProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam)
{
    switch (message) {
    case MSG_CREATE: {
        /* 注册button */
        RegisterMybutton();
        CreateWindow("mybutton", "", WS_VISIBLE | WS_CHILD, IDC_MYBUTTON, 110,
                     80, 70, 20, hWnd, 0);

        break;
    }

    case MSG_CLOSE: {
        DestroyAllControls(hWnd);
        DestroyMainWindow(hWnd);
        PostQuitMessage(hWnd);
        break;
    }

    default:
        break;
    }

    return DefaultPageProc(hWnd, message, wParam, lParam);
}

/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "capture";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = CaptureWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 320;
    CreateInfo.by = 240;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindow(&CreateInfo);

    if (HWND_INVALID == hMainWnd)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup(hMainWnd);

    return 0;
}
