/**
 *   \file src/button.c
 *   \brief write button.c
 *
 *  Detailed description
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDC_LAMIAN 101
#define IDC_CHOUDOUFU 102
#define IDC_JIANBING 103
#define IDC_MAHUA 104
#define IDC_SHUIJIAO 105

#define IDC_XIAN 110
#define IDC_LA 111

#define IDC_PROMPT 200

/* 主界面显示字符串 */
static char *prompts[] = {
    "Northwest pulled noodle is competitive product in the wheaten food",
    "Changsha bad-smelling bean curd is very unique",
    "Shandong thin pancake is difficult to chew",
    "Tianjin fired dough twist is very fragile",
    "Chengdu red oil boiled dumpling is captivating",
};

/* 定义窗口的基本属性 */
static DLGTEMPLATE DlgYourTaste = {
    WS_NONE, WS_EX_NONE, 0,  0,    370, 300, (char *)"你喜欢的口味",
    0,       0,          12, NULL, 0
};

/* 定义窗口的控件 */
static CTRLDATA CtrlYourTaste[] = {
    /* 定义组，可选小吃 */
    { "static", WS_VISIBLE | SS_GROUPBOX, 16, 10, 230, 160, IDC_STATIC,
      (char *)"可选小吃", 0, WS_EX_TRANSPARENT },
    { "button", WS_VISIBLE | BS_AUTORADIOBUTTON | BS_CHECKED | WS_GROUP, 36, 38,
      200, 20, IDC_LAMIAN, "拉面", 0 },
    { "button", WS_VISIBLE | BS_AUTORADIOBUTTON, 36, 64, 200, 20, IDC_CHOUDOUFU,
      (char *)"长沙臭豆腐", 0 },
    { "button", WS_VISIBLE | BS_AUTORADIOBUTTON | WS_DISABLED, 36, 90, 200, 20,
      IDC_JIANBING,(char *) "山东煎饼", 0 },
    { "button", WS_VISIBLE | BS_AUTORADIOBUTTON, 36, 116, 200, 20, IDC_MAHUA,
      (char *)"天津麻花", 0 },
    { "button", WS_VISIBLE | BS_AUTORADIOBUTTON, 36, 142, 200, 20, IDC_SHUIJIAO,
      (char *)"成都水饺", 0 },
    { "static", WS_VISIBLE | SS_GROUPBOX | WS_GROUP, 250, 10, 100, 160,
      IDC_STATIC, (char *)"口味", 0, WS_EX_TRANSPARENT },
    { "button", WS_VISIBLE | BS_AUTOCHECKBOX, 260, 38, 80, 20, IDC_XIAN,
      (char *)"偏咸", 0 },
    { "button", WS_VISIBLE | BS_AUTOCHECKBOX | BS_CHECKED, 260, 64, 80, 20,
      IDC_LA, (char *)"偏辣", 0 },
    { "static", WS_VISIBLE | SS_LEFT | WS_GROUP, 16, 180, 360, 40, IDC_PROMPT,
      (char *)"西北精品", 0 },

    { "button", WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP, 70, 230,
      70, 30, IDOK, "OK", 0 },
    { "button", WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 200, 230, 70, 30,
      IDCANCEL, "Cancel", 0 },
};

/*------------------------------------------------------------------------------
 * 函数名:my_notif_proc
 * 功能描述:提示主界面函数
 * 参数: HWND hwnd
 * 参数:LINT id
 * 参数:int nc ,
 * 被调用:
 * 返回值:static void
 ------------------------------------------------------------------------------*/
static void my_notif_proc(HWND hwnd, LINT id, int nc, DWORD add_data)
{
    if (nc == BN_CLICKED) {
        SetWindowText(GetDlgItem(GetParent(hwnd), IDC_PROMPT),
                      prompts[id - IDC_LAMIAN]);
    }
} /*-------- end my_notif_proc -------- */

/*------------------------------------------------------------------------------
 * 函数名:DialogBoxProc2
 * 功能描述:窗口消息处理函数
 * 参数:HWND hDlg 句柄
 * 参数:UINT message  消息
 * 参数:WPARAM wParam
 * 参数:LPARAM lParam
 * 被调用:
 * 返回值:static LRESULT
 ------------------------------------------------------------------------------*/
static LRESULT DialogBoxProc2(HWND hDlg, UINT message, WPARAM wParam,
                              LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG: { /* 初始化窗口 */
        /* int i; */
        /* for (i = IDC_LAMIAN; i <= IDC_LAMIAN; i++) { */
        /*     SetNotificationCallback(GetDlgItem(hDlg, i), my_notif_proc); */
        /* } */
        break;
    }

    case MSG_COMMAND: {
        switch (wParam) {
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, wParam);
            break;
        default:
            break;
        }
        break;
    }

    default:
        break;
    }

    return DefaultDialogProc(hDlg, message, wParam, lParam);
} /*-------- end DialogBoxProc2 -------- */

/**
 *  \brief main
 *
 *  program entry
 *
 *  \param
 *  \return return type
 */
int MiniGUIMain(int argc, const char *argv[])
{
    /* 控件 */
    DlgYourTaste.controls = CtrlYourTaste;
    /* 定义处理 */
    DialogBoxIndirectParam(&DlgYourTaste, HWND_DESKTOP, DialogBoxProc2, 0L);

    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
