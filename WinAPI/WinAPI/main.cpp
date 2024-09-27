#include <windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Точка входа в систему
INT WINAPI WinMain(HINSTANCE hInstancce, HINSTANCE hPrevInt, LPSTR ipCmdLine, INT nCmdShow)
{
	//hInstancce - эксземпляр запущенного *.exe-файла нашей программы
	//hPrevInt - не используется
	//LPSTR - LongPointer To Streang
	//ipCmdLine - CommandLine (командная строка с параметрами запуска приложения)
	//nCmdShow - режим отображения окна (развернутого на весь экран, свернутого в панель задач и т.д)
	//Префиксы: n..., lp... это Венгерская нотация
	//			n - Number
	//			lp - Long pointer
	//			h - HINSTANCE

	/*MessageBox //wchar_t- 2 байта
	(
		NULL,
		"Hello Windows\nThis is WindowsBox()",
		"Window title",

		//https://learn.microsoft.com/ru-ru/windows/win32/api/winuser/nf-winuser-messagebox
		MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON3 |
		MB_ICONWARNING |
		MB_SYSTEMMODAL

	); */

	DialogBoxParam(hInstancce, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Hendler to Window. Обработчик или дискриптор окна - это число при помощи которого можно обратится к окну
	//uMsg - Massage. Сообщение которое отправляется окну
	//wParam, lParam - это параметры сообщения, у каждого сообщения свой набор параметров.
	//LOWORD - Младшее слово
	//HIWORD - Старшее слово
	//DWORD - Двойное слово

	switch (uMsg)
	{
	case WM_INITDIALOG: //это сообщение отправляется один раз при инициализации окна
		break;
	case WM_COMMAND:	//обрабатывает нажатие кнопок и другие действия пользователя
		//ResourceID
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			// Создаем буфер
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //sz - String Zero (NULL Terminated Line - C-string)
			
			//получаем обработчики текстовых полей
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

			// считываем содержимое поля Login в буфер
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			//записываем полученный текст в текстовое поле Password
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:		//отправляется при нажатии кнопки закрыть (Х)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}