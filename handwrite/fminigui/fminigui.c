/**
 *   \file src/fminigui.c
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

struct timeval cur_time, prev_time;
int gen_millis;
static void InitFlyingGUI(void)
{
	srand( time(NULL));

	
}

static LRESULT FlyingGUIWinProc(HWND hWnd, UINT message, WPARAM wParam,
                                LPARAM lParam)
{
    HDC hdc;

    switch (message) {
    case MSG_CREATE: {
        SetTimer(hwnd, 100, 10);
        break;
    }

    case MSG_TIMER: {
        if (wParam == 100) {
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case MSG_PAINT: {
        hdc = BeginPaint(hWnd);

        EndPaint(hWnd, hdc);
        return 0;
        break;
    }

    case MSG_CLOSE: {
        KillTimer(hWnd, 100);
        DestroyMainWindow(hWnd);
        PostQuitMessage(hWnd);
        return 0;
        break;
    }
    }
    default:
        break;
    }

    return DefaultWindowProc(hWnd, message, wParam, lParam);
}

static void InitCreateInfo(PMAINWINCREATE pCreateInfo)
{
    pCreateInfo->dwStyle = WS_CAPTION | WS_VISIBLE | WS_BORDER;
    pCreateInfo->dwExStyle = WS_EX_NONE;
    pCreateInfo->spCaption = "fminigui";
    pCreateInfo->hMenu = 0;
    pCreateInfo->hCursor = GetSystemCursor(0);
    pCreateInfo->hIcon = 0;
    pCreateInfo->MainWindowProc = FlyingGUIWinProc;
    pCreateInfo->lx = 0;
    pCreateInfo->ty = 0;
    pCreateInfo->rx = 320;
    pCreateInfo->by = 200;
    pCreateInfo->iBkColor = COLOR_black;
    pCreateInfo->dwAddData = 0;
    pCreateInfo->hHosting = HWND_DESKTOP;
} /*-------- end func -------- */

int MiniGUIMain(int argc, const char *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    InitCreateInfo(&CreateInfo);

    hMainWnd = CreateMainWindow(&CreateInfo);
    if (hMainWnd == HWND_INVALID)
        return -1;

    while (GetMessage(&Msg, hMainWnd)) {
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup(hMainWnd);

    return 0;
}
