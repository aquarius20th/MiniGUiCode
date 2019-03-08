/*******************************************************************************
 * 文件名:bmpbkgnd.c
 * 文件描述:src/bmpbkgnd.c
 * 创建日期:2019/03/07 13:27:52
 * 版本：1.0
 *
 * Copyright © 2019/03/07 13:27:52 - 2019/03/07 13:27:52 mengqp.
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

/* 定义背景图片 */
static BITMAP bmp_bkgnd;

/* 定义对话括模板 */
static DLGTEMPLATE DlgBoxInputLen = { WS_NONE, WS_EX_NONE, 0, 0, 800,  480,
                                      "",      0,          0, 4, NULL, 0 };

#define IDC_SIZE_MM 100
#define IDC_SIZE_INCH 110

static CTRLDATA CtrlInputLen[] = {
    { CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, 400, 10, 220, 18, IDC_STATIC,
      "111111", 0, WS_EX_TRANSPARENT },

    { CTRL_SLEDIT, WS_VISIBLE | WS_TABSTOP | WS_BORDER, 400, 40, 220, 24,
      IDC_SIZE_MM, NULL, 0 },

    { CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, 400, 70, 220, 18, IDC_SIZE_INCH,
      "1111113", 0, WS_EX_TRANSPARENT },
    { CTRL_BUTTON, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 470, 110, 60, 25,
      IDOK, "OK", 0 }

};

static void my_notif_proc(HWND hwnd, LINT id, int nc, DWORD add_data)
{
    if (id == IDC_SIZE_MM && nc == EN_CHANGE) {
        char buff[60];
        double len;

        GetWindowText(hwnd, buff, 32);
        len = atof(buff);
        len = len / 25.4;

        sprintf(buff, "Equivalent to %.5f inches", len);

        SetDlgItemText(GetParent(hwnd), IDC_SIZE_INCH, buff);
    }
}

static LRESULT InputLenDialogBoxProc(HWND hDlg, UINT message, WPARAM wParam,
                                     LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
        SetWindowAdditionalData(hDlg, lParam);
        SendDlgItemMessage(hDlg, IDC_SIZE_MM, EM_LIMITTEXT, 15, 0);
        SetNotificationCallback(GetDlgItem(hDlg, IDC_SIZE_MM), my_notif_proc);
        return 1;

    case MSG_ERASEBKGND: {
        HDC hdc = (HDC)wParam;
        const RECT *clip = (const RECT *)lParam;
        BOOL fGetDC = FALSE;
        RECT rcTemp;

        if (hdc == 0) {
            hdc = GetClientDC(hDlg);
            fGetDC = TRUE;
        }

        if (clip) {
            rcTemp = *clip;
            ScreenToClient(hDlg, &rcTemp.left, &rcTemp.top);
            ScreenToClient(hDlg, &rcTemp.right, &rcTemp.bottom);
            IncludeClipRect(hdc, &rcTemp);
        } else
            GetClientRect(hDlg, &rcTemp);

        FillBoxWithBitmap(hdc, 0, 0, RECTW(rcTemp), RECTH(rcTemp), &bmp_bkgnd);

        if (fGetDC)
            ReleaseDC(hdc);
        return 0;
    }

    case MSG_CLOSE:
        EndDialog(hDlg, IDCANCEL);
        break;

    case MSG_COMMAND:
        switch (wParam) {
        case IDOK: {
            char buff[40];
            double *length = (double *)GetWindowAdditionalData(hDlg);
            GetWindowText(GetDlgItem(hDlg, IDC_SIZE_MM), buff, 32);
            *length = atof(buff);
        }
        case IDCANCEL:
            EndDialog(hDlg, wParam);
            break;
        }
        break;
    }

    return DefaultDialogProc(hDlg, message, wParam, lParam);
}

/* 程序入口 */
int MiniGUIMain(int argc, const char *argv[])
{
    double length;
    int rtn;

    /* 加载图片 */
    if (LoadBitmapFromFile(HDC_SCREEN, &bmp_bkgnd, "res/bkgnd.jpg")) {
        return 1;
    }

    /* 控制窗口 */
    DlgBoxInputLen.controls = CtrlInputLen;
    rtn = DialogBoxIndirectParam(&DlgBoxInputLen, HWND_DESKTOP,
                                 InputLenDialogBoxProc, (LPARAM)length);
    if (IDOK == rtn) {
        printf("The length is %.5f mm.\n", length);
    }

    /* 载出图片 */
    UnloadBitmap(&bmp_bkgnd);
    return 0;
}
