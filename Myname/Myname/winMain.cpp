#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _IpszClass = TEXT("구구단");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT rt;
int axis_X = 100; //기준이 되는x축
int axis_Y = 100; //기준이 되는y축
int multiplicationNum = 1;

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR IpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = _IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	_hWnd = CreateWindow(
		_IpszClass,
		_IpszClass,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		800,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paint; //페인트 구조체
	
	int multy_y = 100;
	if (axis_X >= 300)
	{
		multy_y = 300;
	}
	else if (axis_X >= 300 && multy_y == 300)
	{
		multy_y = 500;
	}

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &paint);
		MoveToEx(hdc, 70, 50, NULL); 
		LineTo(hdc, 130, 50);
		MoveToEx(hdc, 40, 70, NULL);
		LineTo(hdc, 160, 70);
		MoveToEx(hdc, 80, 90, NULL);
		LineTo(hdc, 110, 90);
		MoveToEx(hdc, 80, 90, NULL);
		LineTo(hdc, 70, 100);
		MoveToEx(hdc, 70, 100, NULL);
		LineTo(hdc, 70, 110);
		MoveToEx(hdc, 70, 110, NULL);
		LineTo(hdc, 80, 120);
		MoveToEx(hdc, 80, 120, NULL);
		LineTo(hdc, 110, 120);
		MoveToEx(hdc, 110, 120, NULL);
		LineTo(hdc, 120, 110);
		MoveToEx(hdc, 120, 110, NULL);
		LineTo(hdc, 120, 100);
		MoveToEx(hdc, 120, 100, NULL);
		LineTo(hdc, 110, 90);
		//ㅎ
		MoveToEx(hdc, 95, 130, NULL);
		LineTo(hdc, 95, 140);
		MoveToEx(hdc, 60, 140, NULL);
		LineTo(hdc, 140, 140);
		//ㅗ
		MoveToEx(hdc, 80, 150, NULL);
		LineTo(hdc, 110, 150);
		MoveToEx(hdc, 80, 150, NULL);
		LineTo(hdc, 70, 160);
		MoveToEx(hdc, 70, 160, NULL);
		LineTo(hdc, 70, 170);
		MoveToEx(hdc, 70, 170, NULL);
		LineTo(hdc, 80, 180);
		MoveToEx(hdc, 80, 180, NULL);
		LineTo(hdc, 110, 180);
		MoveToEx(hdc, 110, 180, NULL);
		LineTo(hdc, 120, 170);
		MoveToEx(hdc, 120, 170, NULL);
		LineTo(hdc, 120, 160);
		MoveToEx(hdc, 120, 160, NULL);
		LineTo(hdc, 110, 150);
		//ㅇ

		MoveToEx(hdc, 180, 60, NULL);
		LineTo(hdc, 240, 60);
		MoveToEx(hdc, 240, 60, NULL);
		LineTo(hdc, 180, 120);
		MoveToEx(hdc, 210, 90, NULL);
		LineTo(hdc, 240, 120);
		//ㅈ
		MoveToEx(hdc, 180, 140, NULL);
		LineTo(hdc, 240, 140);
		MoveToEx(hdc, 210, 140, NULL);
		LineTo(hdc, 210, 160);
		//ㅜ
		MoveToEx(hdc, 300, 50, NULL);
		LineTo(hdc, 360, 50);
		MoveToEx(hdc, 270, 70, NULL);
		LineTo(hdc, 390, 70);
		MoveToEx(hdc, 310, 90, NULL);
		LineTo(hdc, 340, 90);
		MoveToEx(hdc, 310, 90, NULL);
		LineTo(hdc, 300, 100);
		MoveToEx(hdc, 300, 100, NULL);
		LineTo(hdc, 300, 110);
		MoveToEx(hdc, 300, 110, NULL);
		LineTo(hdc, 310, 120);
		MoveToEx(hdc, 310, 120, NULL);
		LineTo(hdc, 340, 120);
		MoveToEx(hdc, 340, 120, NULL);
		LineTo(hdc, 350, 110);
		MoveToEx(hdc, 350, 110, NULL);
		LineTo(hdc, 350, 100);
		MoveToEx(hdc, 350, 100, NULL);
		LineTo(hdc, 340, 90);
		//ㅎ
		MoveToEx(hdc, 400, 50, NULL);
		LineTo(hdc, 400, 160);
		MoveToEx(hdc, 360, 100, NULL);
		LineTo(hdc, 400, 100);
		MoveToEx(hdc, 360, 120, NULL);
		LineTo(hdc, 400, 120);
		//ㅕ
		MoveToEx(hdc, 340, 150, NULL);
		LineTo(hdc, 370, 150);
		MoveToEx(hdc, 340, 150, NULL);
		LineTo(hdc, 330, 160);
		MoveToEx(hdc, 330, 160, NULL);
		LineTo(hdc, 330, 170);
		MoveToEx(hdc, 330, 170, NULL);
		LineTo(hdc, 340, 180);
		MoveToEx(hdc, 340, 180, NULL);
		LineTo(hdc, 370, 180);
		MoveToEx(hdc, 370, 180, NULL);
		LineTo(hdc, 380, 170);
		MoveToEx(hdc, 380, 170, NULL);
		LineTo(hdc, 380, 160);
		MoveToEx(hdc, 380, 160, NULL);
		LineTo(hdc, 370, 150);
		//ㅇ
		EndPaint(hWnd, &paint);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}