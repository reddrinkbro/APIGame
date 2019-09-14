#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _IpszClass = TEXT("구구단");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT rt; //안보이는 사각형을 만들기 위한 선언
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
	char str[100];
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd); //DC생성
			
		if (axis_X == 400 && axis_Y == 100) //제일 위쪽 오른쪽일 경우
		{
			axis_X = 100;
			axis_Y = 300; //중간좌표로 설정
		}
		else if (axis_X == 400 && axis_Y == 300) // 중간 오른쪽일 경우
		{
			axis_X = 100;
			axis_Y = 500; //제일 밑좌표로 설정
		}
		for (int j = 1; j < 10; j++)
		{
			if (multiplicationNum <10) //10미만일때만 출력
			{
				wsprintf(str, TEXT("%d x %d = %d "), multiplicationNum, j, multiplicationNum*j); 
				TextOut(hdc, axis_X, axis_Y, str, strlen(str));
				axis_Y += 15;//구구단 출력
			}
		}
		if (axis_Y < 300) // y축 계속 초기화
		{
			axis_Y = 100;
		}
		else if (axis_Y < 500 && axis_Y >= 300)
		{
			axis_Y = 300;
		}
		else if (axis_Y >= 500)
		{
			axis_Y = 500;
		}
		if (multiplicationNum < 10) //10미만일떄 만 증가하고 x축이 더해진다. 최대 값은 10이 된다
		{
			multiplicationNum++;
			axis_X = axis_X + 100;
		}
		ReleaseDC(hWnd, hdc);
		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		
		if (multiplicationNum > 1) //1보다 크면 값을 줄여준다
		{
			multiplicationNum--;
		}
		if (multiplicationNum == 3) // 3이 되면 좌표값을 수정한다
		{
			axis_X = 300;
			axis_Y = 100;
		}
		else if (multiplicationNum == 6) //6이되면 좌표값을 수정한다
		{
			axis_X = 300;
			axis_Y = 300;
		}
		else //그 외는 x값만 줄어든다
		{
			if (axis_X != 100) //x축이 100미만으로 떨어지지 않는다.
			{
				axis_X = axis_X - 100;
			}
		}
		if (multiplicationNum > 1) //1보다 클때는 삭제가 가능하다
		{
			SetRect(&rt, axis_X, axis_Y, axis_X + 75, axis_Y + 140); // 변경이 일어나는 부분을 지정한다.
			InvalidateRect(hWnd, &rt, TRUE);
		}
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}