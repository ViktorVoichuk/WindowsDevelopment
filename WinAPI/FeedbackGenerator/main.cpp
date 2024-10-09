#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* SZ_PROPERTIES[] =
{
    "понимает материал",
    "внимательный",
    "хорошо пишет код",
    "не выполняет домашние задания",
    "прогуливает занятия"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
    return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_SETTEXT, 0, (LPARAM)"Введите Фамилию Имя Отчество поностью");
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE_DESCR = 2048, SIZE = 256;
            CHAR sz_fullname[SIZE]{};
            CHAR sz_description[SIZE_DESCR]{ "Введите Фамилию Имя Отчество поностью" };
            HWND hEditName = GetDlgItem(hwnd, IDC_EDIT_NAME);
            HWND hEditDescription = GetDlgItem(hwnd, IDC_EDIT_DESCRIPTION);
            SendMessage(hEditName, WM_GETTEXT, SIZE, (LPARAM)sz_fullname);
            if (strcmp(sz_description, sz_fullname) == 0 || strcmp(sz_fullname, "") == 0)
            {
                SendMessage(hEditDescription, WM_SETTEXT, 0, (LPARAM)"Вы не ввели Ф.И.О студента");
            }
            else
            {
                
                strcpy(sz_description, sz_fullname);
                sprintf(sz_fullname, "Характеристики студента: %s", sz_description);
                SendMessage(GetDlgItem(hwnd, IDC_STATIC_CHARACTER), WM_SETTEXT, 0, (LPARAM)sz_fullname);
                for (int i = 0; i < 5; i++)
                {
                    HWND hCheck = GetDlgItem(hwnd, IDC_CHECK_UNDERSTANDING + i);
                    if (SendMessage(hCheck, BM_GETCHECK, 0, 0) == BST_CHECKED)
                        sprintf(sz_description, "%s, %s", sz_description, SZ_PROPERTIES[i]);
                }

                SendMessage(hEditDescription, WM_SETTEXT, 0, (LPARAM)sz_description);
            }
        }
        break;
        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
    }
    return FALSE;
}