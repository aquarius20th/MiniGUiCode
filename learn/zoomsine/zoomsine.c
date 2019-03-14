/**
 *   \file zoomsine.c
 *   \brief 做一个可以放大缩小的正弦图
 */

#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "sinewave.h"

static int radius = 0;
static RECT rcCircle = { 10, 100, 790, 380 };
static void my_notif_proc(HWND hwnd, LINT id, int nc, DWORD add_data)
{
    if (nc == TBN_CHANGE) {
        radius = SendMessage(hwnd, TBM_GETPOS, 0, 0);
        InvalidateRect(GetParent(hwnd), &rcCircle, TRUE);
    }
}

static LRESULT TrackBarWinProc(HWND hWnd, UINT message, WPARAM wParam,
                               LPARAM lParam)
{
    HWND hwnd;
    switch (message) {
    case MSG_CREATE:
        hwnd = CreateWindow(CTRL_TRACKBAR, "", WS_VISIBLE | TBS_NOTIFY, 100, 10,
                            10, 210, 50, hWnd, 0);

        SendMessage(hwnd, TBM_SETRANGE, 0, 80);
        SendMessage(hwnd, TBM_SETLINESIZE, 1, 0);
        SendMessage(hwnd, TBM_SETPAGESIZE, 10, 0);
        SendMessage(hwnd, TBM_SETTICKFREQ, 10, 0);
        SendMessage(hwnd, TBM_SETPOS, radius, 0);

        SetNotificationCallback(hwnd, my_notif_proc);
        SetFocus(hwnd);

        sinewave_get_a_circle(0);
        break;

    case MSG_PAINT: {
        int i;
        int width = rcCircle.right - rcCircle.right;
        double x, y;
        double tmp_x, tmp_y;

        HDC hdc = BeginPaint(hWnd);

        SetBrushColor(hdc, PIXEL_blue);
        FillCircle(hdc, 10, 10, 8);

        for (i = 0; i < 180; i++) {
            sinewave_get_circle(i, &x, &y);
            tmp_x = x * radius * 5 + 10;
            tmp_y = y * radius * 2 + 240;

            /* printf("radius = %d tmp_x=%f tmp_y=%f\n", radius, tmp_x, tmp_y); */
            /* BitBlt(hdc, 0, 0, 10, 10, hdc, tmp_x + 10, tmp_y + 240, 0); */
			SetPixel(hdc, tmp_x, tmp_y, PIXEL_red );
        }
        /* ClipRectIntersect (hdc, &rcCircle); */
        /* Circle (hdc, 100, 180, radius); */

        EndPaint(hWnd, hdc);
        return 0;
    }

    case MSG_DESTROY:
        DestroyAllControls(hWnd);
        return 0;

    case MSG_CLOSE:
        DestroyMainWindow(hWnd);
        PostQuitMessage(hWnd);
        return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}
/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle = WS_CAPTION | WS_BORDER | WS_VISIBLE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "zoomsine";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(IDC_ARROW);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = TrackBarWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 800;
    CreateInfo.by = 480;
    CreateInfo.iBkColor = GetWindowElementColor(WE_MAINC_THREED_BODY);
    CreateInfo.dwAddData = 0;
    CreateInfo.dwReserved = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindow(&CreateInfo);
    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup(hMainWnd);

    return 0;
}
