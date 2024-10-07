#include <windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);//cb - Count Bytes
	wClass.cbClsExtra = 0;// Class Extra Bytes
	wClass.cbWndExtra = 0;// Window Extra Bytes

	//Appearance(внешний вид):
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);// Small Icon
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;


	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	HWND hwnd = CreateWindowEx
	(
		NULL,//Window ExStyle
		g_sz_WINDOW_CLASS,//Window Class Name
		g_sz_WINDOW_CLASS,//Window Title
		WS_OVERLAPPEDWINDOW,//Window Style
		CW_USEDEFAULT, CW_USEDEFAULT,//Coordinates
		CW_USEDEFAULT, CW_USEDEFAULT,//window size
		NULL,//Parent
		NULL,//hMenu: Для главного окна это ResourseID главного меню,
		//Для дочернего окна(кнопки и другие элементы) - это ID - русурса соответствующего элемента(кнопки, текстового поля и т.д. расположенных на главном окне)
		//по этому ResourceID мы находим дочерний элемент окна при помощи функции GetDlgItem()
		//
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);// задает режим отображения окна(развернуто, свернуто в окно, свернуто в панель задач)
	UpdateWindow(hwnd);// Прорисовывает окно

	//3 - Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		return msg.message;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_COMMAND:
	{
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}