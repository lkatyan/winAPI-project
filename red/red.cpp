#include "framework.h"
#include "red.h"
#include <xstring>
#include <windows.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog1(HWND, UINT, WPARAM, LPARAM);
static int id = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_RED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RED));



	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RED));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RED);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > String;
	PAINTSTRUCT ps;
	HDC hdc;
	int x, y;
	static int xx = 0, yy = 0;
	static String str;
	static TCHAR ss1_str[] = _T("Слово1");
	static TCHAR ss2_str[] = _T("Слово2");
	static TCHAR ss3_str[] = _T("Слово3");

	static TCHAR r_str[] = _T("Нажата правая кнопка мыши");
	static TCHAR l_str[] = _T("Нажата левая кнопка мыши");

	static HFONT hFont, hOldFont;

	switch (message)
	{
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		TextOut(hdc, x, y, r_str, _tcsclen(r_str));
		xx = x; yy = y;
		str.clear();
		if (id == 0) str += r_str;
		else if (id == 1) str += ss1_str;
		else if (id == 2) str += ss2_str;
		else if (id == 3) str += ss3_str;
		ReleaseDC(hWnd, hdc);
		break;
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		if (id == 0) str += l_str;
		else if (id == 1) str += ss1_str;
		else if (id == 2) str += ss2_str;
		else if (id == 3) str += ss3_str;
		TextOut(hdc, x, y, l_str, _tcsclen(l_str));
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		str += (TCHAR)wParam;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{

		case IDM_DIALOG1:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog1);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_FIRSTWORD:
			id = 1;
			break;
		case IDM_SECONDWORD:
			id = 2;
			break;
		case IDM_THIRDWORD:
			id = 3;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		static LOGFONT lf;
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfPitchAndFamily = DEFAULT_PITCH;
		lf.lfHeight = 20;
		lf.lfWeight = 40;
		lf.lfEscapement = 0;
		hFont = CreateFontIndirect(&lf);
		SelectObject(hdc, hFont);

		TextOut(hdc, xx, yy, str.data(), str.size());
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		return 0;
	}
	return 0;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK: {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE; }
		case IDCANCEL: {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE; }
		case IDFWORD2: {
			id = 1;
			break; }
		case IDSWORD2: {
			id = 2;
			break; }
		case IDTWORD2: {
			id = 3;
			break; }
		}
		break;
		}
		return (INT_PTR)FALSE;
	}
}