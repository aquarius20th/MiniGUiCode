/**
 *   \file src/combobox.c
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

char date[1024] = "Your date : You will meet %s at %d:%d";

static const char *daxia[] = {
    "Zeus", "Pan", "Apollo", "Heracles", "Achilles", "Jason", "Theseus",
};

static const char *daxia_char[] = {
    "Zeus is the leader of the gods and god of the sky and thunder in Greek "
    "mythology.",
    "Pan  is the Greek god who watches over shepherds and their flocks.",
    "Apollo is a god in Greek and Roman mythology, the son of Zeus and Leto, "
    "and the twin of Artemis.",
    "Heracles was the greatest of the mythical Greek heroes, best known for "
    "his superhuman strength and many stories are told of his life.",
    "Achilles was the greatest warrior in the Trojan War.",
    "Jason is a hero of Greek mythology. His father was Aeson, the rightful "
    "king of Iolcus.",
    "Theseus was a legendary king of Athens. Theseus was considered by "
    "Athenians as the great reformer.",
};

#define IDC_HOUR 100
#define IDC_MINUTE 110
#define IDC_SECOND 120
#define IDL_DAXIA 200

#define IDC_PROMPT 300

/* 窗口控件 */
static CTRLDATA CtrlMyDate[] = {
    { "static", WS_CHILD | SS_RIGHT | WS_VISIBLE, 10, 20, 90, 20, IDC_STATIC,
      "i will at", 0 },
    { CTRL_COMBOBOX,
      WS_CHILD | CBS_READONLY | CBS_AUTOSPIN | CBS_AUTOLOOP | WS_VISIBLE, 100,
      18, 40, 20, IDC_HOUR, "", WS_EX_TRANSPARENT },
    { "static", WS_CHILD | SS_CENTER | WS_VISIBLE, 140, 20, 20, 20, IDC_STATIC,
      ":", 0 },
    { CTRL_COMBOBOX,
      WS_CHILD | WS_VISIBLE | CBS_READONLY | CBS_AUTOSPIN | CBS_AUTOLOOP, 160,
      18, 40, 20, IDC_MINUTE, "", 0 },
    { "static", WS_CHILD | SS_CENTER | WS_VISIBLE, 200, 20, 40, 20, IDC_STATIC,
      "meet", 0 },
    { CTRL_COMBOBOX, WS_VISIBLE | CBS_DROPDOWNLIST | CBS_NOTIFY, 240, 15, 100,
      25, IDL_DAXIA, "", 80 },
    { "static", WS_CHILD | SS_LEFT | WS_VISIBLE, 15, 50, 280, 70, IDC_PROMPT,
      "11111", 0 },
    { CTRL_BUTTON, WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP, 30,
      120, 70, 25, IDOK, "ok", 0 },
    { "button", WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 260, 120, 70, 25,
      IDCANCEL, "cancel", 0 },
};

/* 窗口 */
static DLGTEMPLATE DlgMyDate = { WS_BORDER | WS_CAPTION,
                                 WS_EX_NONE,
                                 100,
                                 100,
                                 360,
                                 180,
                                 "meeting plan",
                                 0,
                                 0,
                                 TABLESIZE(CtrlMyDate),
                                 NULL,
                                 0 };

static void daxia_notif_proc(HWND hwnd, LINT id, int nc, DWORD add_data)
{
    if (nc == CBN_SELCHANGE) {
        int cur_sel = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
        if (cur_sel >= 0) {
            SetWindowText(GetDlgItem(GetParent(hwnd), IDC_PROMPT),
                          daxia_char[cur_sel]);
        }
    }
}

static void prompt(HWND hDlg)
{
    int hour = SendDlgItemMessage(hDlg, IDC_HOUR, CB_GETSPINVALUE, 0, 0);
    int min = SendDlgItemMessage(hDlg, IDC_MINUTE, CB_GETSPINVALUE, 0, 0);
    int sel = SendDlgItemMessage(hDlg, IDL_DAXIA, CB_GETCURSEL, 0, 0);

    sprintf(date, daxia[sel], hour, min);
    MessageBox(hDlg, date, "meet plan", MB_OK | MB_ICONINFORMATION);
}

/* 窗口处理函数 */
static LRESULT MyDateBoxProc(HWND hDlg, UINT message, WPARAM wParam,
                             LPARAM lParam)
{
    int i;
    switch (message) {
    case MSG_INITDIALOG: {
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINFORMAT, 0,
                           (LPARAM) "%02d");
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINRANGE, 0, 23);
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINVALUE, 20, 0);
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINPACE, 1, 1);

        SendDlgItemMessage(hDlg, IDC_MINUTE, CB_SETSPINFORMAT, 0,
                           (LPARAM) "%02d");
        SendDlgItemMessage(hDlg, IDC_MINUTE, CB_SETSPINRANGE, 0, 59);
        SendDlgItemMessage(hDlg, IDC_MINUTE, CB_SETSPINVALUE, 0, 0);
        SendDlgItemMessage(hDlg, IDC_MINUTE, CB_SETSPINPACE, 1, 2);

        for (i = 0; i < 7; i++) {
            SendDlgItemMessage(hDlg, IDL_DAXIA, CB_ADDSTRING, 0,
                               (LPARAM)daxia[i]);
        }

        SetNotificationCallback(GetDlgItem(hDlg, IDL_DAXIA), daxia_notif_proc);
        SendDlgItemMessage(hDlg, IDL_DAXIA, CB_SETCURSEL, 0, 0);
        break;
    }

    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
            prompt(hDlg);
        case IDCANCEL:
            EndDialog(hDlg, wParam);
            break;
        }
        break;
    default:
        break;
    }
    return DefaultDialogProc(hDlg, message, wParam, lParam);
}

/* main entry */
int MiniGUIMain(int argc, const char *argv[])
{
    DlgMyDate.controls = CtrlMyDate;
    DialogBoxIndirectParam(&DlgMyDate, HWND_DESKTOP, MyDateBoxProc, 0L);

    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
