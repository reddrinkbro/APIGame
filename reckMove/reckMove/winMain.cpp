#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _IpszClass = TEXT("사각형옮기기");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT userRc = { 100, 100, 200, 200 };
RECT computerRC = { 500, 500, 600, 600 };
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
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &paint);
		Rectangle(hdc, userRc.left, userRc.top, userRc.right, userRc.bottom); //키보드로 움직이는 사각형
		Rectangle(hdc, computerRC.left, computerRC.top, computerRC.right, computerRC.bottom); //움지이게 만들어야 하는 사각형
		EndPaint(hWnd, &paint);
		break;
	case WM_KEYDOWN: //키보드 키가 눌렸을때 메세지 발생
		switch (wParam)
		{
		case VK_LEFT:	//왼쪽 방향키
			if (userRc.left != 0) // 제일 왼쪽이 아닐때
			{
				userRc.left -= 10;
				userRc.right -= 10;
				//플레이어가 움직이는 사각형의 왼쪽이 움직이게 되는 사각형의 오른쪽보다 작아지게 되는 경우
				//플레이어가 움직이는 사각형의 왼쪽이 움직이게 되는 사각형의 왼쪽보다 큰 경우
				//움직이게 되는 사각형의 오른쪽 위 모서리에서 아래 모서리까지 범위에 있을경우
				//움직이게 되는 사각형이 제일 왼쪽이 아닐떄
				if ((userRc.left < computerRC.right && userRc.left > computerRC.left) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.left != 0)
				{
					computerRC.left -= 10;
					computerRC.right -= 10;
				}
				//움직이게 되는 사각형이 제일 왼쪽 일떄
				else if ((userRc.left < computerRC.right && userRc.left > computerRC.left) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.left == 0)
				{
					userRc.left += 10;
					userRc.right += 10;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_RIGHT:	//오른쪽 방향키
			if (userRc.right != 780)// 제일 오른쪽이 아닐때
			{
				userRc.left += 10;
				userRc.right += 10;
				//플레이어가 움직이는 사각형의 오른쪽이 움직이게 되는 사각형의 왼쪽보다 커지게 되는 경우
				//플레이어가 움직이는 사각형의 오른쪽이 움직이게 되는 사각형의 오른쪽보다 작은 경우
				//움직이게 되는 사각형의 왼쪽 위 모서리에서 아래 모서리까지 범위에 있을경우
				//움직이게 되는 사각형이 제일 오른쪽이 아닐떄
				if ((userRc.right > computerRC.left && userRc.right < computerRC.right) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.right!=780)
				{
					computerRC.left += 10;
					computerRC.right += 10;
				}
				//움직이게 되는 사각형이 제일 오른쪽 일떄
				else if ((userRc.right > computerRC.left && userRc.right < computerRC.right) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.right == 780)
				{
					userRc.left -= 10;
					userRc.right -= 10;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_UP: //위쪽 방향키
			if (userRc.top != 0)// 제일 위쪽이 아닐때
			{
				userRc.top -= 10;
				userRc.bottom -= 10;
				//플레이어가 움직이는 사각형의 위쪽이 움직이게 되는 사각형의 아래쪽보다 작아지게 되는 경우
				//플레이어가 움직이는 사각형의 위쪽이 움직이게 되는 사각형의 위쪽보다 큰 경우
				//움직이게 되는 사각형의 아래쪽 왼쪽 모서리에서 오른쪽 모서리까지 범위에 있을경우
				//움직이게 되는 사각형이 제일 위쪽이 아닐떄
				if ((userRc.top < computerRC.bottom && userRc.top > computerRC.top) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.top !=0)
				{
					computerRC.top -= 10;
					computerRC.bottom -= 10;
				}
				//움직이게 되는 사각형이 제일 위쪽 일떄
				else if ((userRc.top < computerRC.bottom && userRc.top > computerRC.top) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.top == 0)
				{
					userRc.top += 10;
					userRc.bottom += 10;
				}

				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_DOWN://아래쪽 방향키
			if (userRc.bottom != 760)// 제일 아래쪽이 아닐때
			{
				userRc.top += 10;
				userRc.bottom += 10;
				//플레이어가 움직이는 사각형의 아래쪽이 움직이게 되는 사각형의 위쪽보다 커지게 되는 경우
				//플레이어가 움직이는 사각형의 아래쪽이 움직이게 되는 사각형의 아래쪽보다 큰 경우
				//움직이게 되는 사각형의 위쪽 왼쪽 모서리에서 오른쪽 모서리까지 범위에 있을경우
				//움직이게 되는 사각형이 제일 아래쪽이 아닐떄
				if ((userRc.bottom > computerRC.top && userRc.bottom < computerRC.bottom) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.bottom != 760)
				{
					computerRC.top += 10;
					computerRC.bottom += 10;
				}
				//움직이게 되는 사각형이 제일 아래쪽 일떄
				else if ((userRc.bottom > computerRC.top && userRc.bottom < computerRC.bottom) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.bottom == 760)
				{
					userRc.top -= 10;
					userRc.bottom -= 10;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}