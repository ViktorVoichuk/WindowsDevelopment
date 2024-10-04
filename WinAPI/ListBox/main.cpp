//ListBox
//#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This","is","my","First","List","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, (DLGPROC)DlgProcAdd, 0);
			break;

		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hCombo, LB_GETCURSEL, 0, 0);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hCombo, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE] = "�� ������ �� �������.";
			if (i != LB_ERR)
				sprintf(sz_message, "�� ������� ����� � %i �� ��������� \"%s\"", i, (LPARAM)sz_buffer);
			//sprintf - ��������� �������������� �����, ��������� �������� � ������
			//������������� %i - ��� ����� �����, %s - ������
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hListBox, LB_FINDSTRING, -1, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
				MessageBox(hwnd, "����� ���� ��� ����������", "Info", MB_OK | MB_ICONINFORMATION);
		}
			
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