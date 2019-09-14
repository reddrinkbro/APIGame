#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _IpszClass = TEXT("������");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT rt; //�Ⱥ��̴� �簢���� ����� ���� ����
int axis_X = 100; //������ �Ǵ�x��
int axis_Y = 100; //������ �Ǵ�y��
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
	PAINTSTRUCT paint; //����Ʈ ����ü
	char str[100];
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd); //DC����
			
		if (axis_X == 400 && axis_Y == 100) //���� ���� �������� ���
		{
			axis_X = 100;
			axis_Y = 300; //�߰���ǥ�� ����
		}
		else if (axis_X == 400 && axis_Y == 300) // �߰� �������� ���
		{
			axis_X = 100;
			axis_Y = 500; //���� ����ǥ�� ����
		}
		for (int j = 1; j < 10; j++)
		{
			if (multiplicationNum <10) //10�̸��϶��� ���
			{
				wsprintf(str, TEXT("%d x %d = %d "), multiplicationNum, j, multiplicationNum*j); 
				TextOut(hdc, axis_X, axis_Y, str, strlen(str));
				axis_Y += 15;//������ ���
			}
		}
		if (axis_Y < 300) // y�� ��� �ʱ�ȭ
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
		if (multiplicationNum < 10) //10�̸��ϋ� �� �����ϰ� x���� ��������. �ִ� ���� 10�� �ȴ�
		{
			multiplicationNum++;
			axis_X = axis_X + 100;
		}
		ReleaseDC(hWnd, hdc);
		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		
		if (multiplicationNum > 1) //1���� ũ�� ���� �ٿ��ش�
		{
			multiplicationNum--;
		}
		if (multiplicationNum == 3) // 3�� �Ǹ� ��ǥ���� �����Ѵ�
		{
			axis_X = 300;
			axis_Y = 100;
		}
		else if (multiplicationNum == 6) //6�̵Ǹ� ��ǥ���� �����Ѵ�
		{
			axis_X = 300;
			axis_Y = 300;
		}
		else //�� �ܴ� x���� �پ���
		{
			if (axis_X != 100) //x���� 100�̸����� �������� �ʴ´�.
			{
				axis_X = axis_X - 100;
			}
		}
		if (multiplicationNum > 1) //1���� Ŭ���� ������ �����ϴ�
		{
			SetRect(&rt, axis_X, axis_Y, axis_X + 75, axis_Y + 140); // ������ �Ͼ�� �κ��� �����Ѵ�.
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