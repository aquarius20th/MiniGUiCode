/**
 *   \file src/coolbar.c
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define ITEM_NUM	10

static const char* caption[] =
{
   "0", "1", "2", "3", "4", "5","6", "7", "8", "9"
};

static void create_coolbar(HWND hWnd)
{
    HWND cb;
    COOLBARITEMINFO item;
    int i;

    cb = CreateWindow(CTRL_COOLBAR, "", WS_CHILD | WS_VISIBLE | WS_BORDER, 100,
                      10, 100, 100, 20, hWnd, 0);
	item.ItemType = TYPE_TEXTITEM;
	item.Bmp = NULL;
	item.dwAddData = 0;
	for (i = 0; i < ITEM_NUM; ++i) {
		item.insPos = i;
		item.id = i;
		item.Caption = caption[i];
		item.ItemHint = NULL;
		SendMessage( cb, CBM_ADDITEM, 0, (LPARAM)&item );
		if ( i == 3) {
			SendMessage(cb, CBM_ENABLE, i, FALSE);
		}
	}

}

/* main proc */
static LRESULT CoolbarWinProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam)
{
    static HWND ed;
    switch (message) {
    case MSG_CREATE: {
        ed = CreateWindow(CTRL_SLEDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                          200, 10, 10, 100, 20, hWnd, 0);

		create_coolbar( hWnd );
        break;
    }
	case MSG_COMMAND: {
		int id = LOWORD( wParam );
		int code = HIWORD( wParam );
		if ( id == 100 ) {
			PostMessage( ed, MSG_CHAR, '0'+code, 0);
		}
		break;
	}
	case MSG_DESTROY: {
		DestroyAllControls( hWnd );
		break;
	}
	case MSG_CLOSE: {
		DestroyMainWindow( hWnd );
		PostQuitMessage( hWnd );
		break;
	}
    default:
        break;
    }

    return DefaultWindowProc(hWnd, message, wParam, lParam);
}

/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle = WS_CAPTION | WS_BORDER | WS_VISIBLE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "coolbar";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(IDC_ARROW);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = CoolbarWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 300;
    CreateInfo.by = 220;
    CreateInfo.iBkColor =
        GetWindowElementPixel(HWND_DESKTOP, WE_MAINC_THREED_BODY);
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
