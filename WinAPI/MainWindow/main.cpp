#include <windows.h>

#define IDC_STATIC 1000  //1) Создаем ResourxeID для дочернего элемента
#define IDC_EDIT 1001
#define IDC_BUTTON 1002

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
    wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\Cloud.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\Moon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);// Small Icon
    wClass.hCursor = (HCURSOR)LoadImage(hInstance, "CUR\\Normal.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
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

    //2 - создание окна
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
        CreateWindowEx
        (
            NULL,
            "Static",
            "Это Static_text",
            WS_CHILD | WS_VISIBLE,   //Для всех дочерних окон стиль обязательно будет WS_CHILD и WS_VISIBLE
            100, 10,
            200, 20,
            hwnd,
            (HMENU)IDC_STATIC,
            GetModuleHandle(NULL),
            NULL

        );

        CreateWindowEx
        (
            NULL, "Edit", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            100, 30,
            200, 20,
            hwnd,
            (HMENU)IDC_EDIT,
            GetModuleHandle(NULL),
            NULL
        );

        CreateWindowEx
        (
            NULL, "Button", "Применить",
            WS_CHILD | WS_VISIBLE,
            200, 55,
            100, 32,
            hwnd,
            (HMENU)IDC_BUTTON,
            GetModuleHandle(NULL),
            NULL
        );
        
        break;
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE]{};
            HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
            SendMessageA(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

            HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
            SendMessageA(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
            SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
        }
            break;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
    case WM_CLOSE:DestroyWindow(hwnd); break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return FALSE;
}