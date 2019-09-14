#include "stdafx.h"

//=====================
//	## �������� ##
//=====================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
bool mouseClick = false; //���콺�� Ŭ���ߴ��� Ȯ���ϴ� ����
int sizeX = 100; //x���� ���� ��ȭ��
int sizeY = 100; //y���� ���� ��ȭ��
//======================
//	## �Լ� ���漱�� ##
//======================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

RECT _rc1;

//=======================
//	## ������ �����Լ� ##
//=======================
int APIENTRY WinMain(HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	//�ν��Ͻ��� ���������� ��Ƶд�
	_hInstance = hInstance;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü

	//������ ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���콺 Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������
	wndClass.hInstance = hInstance;									//�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ����ǥ X
		WINSTARTY,				//������ ȭ����ǥ Y
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//������ �� �ڽ� �����츦 �����ϸ� �������ְ� �׷��� ������ NULL
	);

	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);
	
	//MSG : �ü������ �����ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;
	//�޼��� ����
	//GetMessage : �޼����� ������ �� ���������� �����ִ� �Լ�
	//PeekMessage : �޼����� ������ ���ϵǴ� �Լ�

	//���ӿ�
	/*
	while (true) 
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	*/

	//TranslateMessage : Ű���� �Է¸޼��� ó���� ���
	//�Էµ� Ű�� ����Ű���� Ȯ���� �빮�� Ȥ�� �ҹ���, �ѱ�, ���������� ���� 
	//WM_CHAR �޼��� �߻���Ų��
	//DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �������ش�

	//�Ϲ� ���α׷��ֿ�
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

//������ ���ν��� : �޼����� �ü���� �����ϰ� �ڵ��ϴ� ����
//hWnd : ��� �����쿡�� �߻��� �޼������� ����
//iMessage : �޼��� ���� ��ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� ����
//lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����(x, y)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		
	PAINTSTRUCT ps; 
	static POINT pt = { 0, 0 };
	
	char str[128];
	switch (iMessage)
	{
	case WM_CREATE: //������ == �ʱ�ȭ
		_rc1 = RectMakeCenter(WINSIZEX / 2 , WINSIZEY / 2, 100, 100);
		break;

	case WM_PAINT:	//��¿� ���� ������ ����Ѵ�(����, �׸�, ������� ȭ�鿡 ���̴� ����)
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom); //�簢�� ����
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN: //���콺 ���� ��ư�� �������� �޼��� �߻�
		mouseClick = true; // Ŭ�� ������ true�� �ȴ�
		break;
	case WM_RBUTTONDOWN: //���콺 ������ ��ư�� �������� �޼��� �߻�
		break;
	case WM_LBUTTONUP:
		mouseClick = false; // ���콺Ŭ���� ���� false�� �ȴ�.
		break;
	case WM_MOUSEMOVE:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (pt.x < _rc1.left + 10 && pt.x > _rc1.left - 10  && mouseClick == true) // �簢���� ������ ������
		{
			_rc1.left = pt.x;
			if (pt.y < _rc1.top + 10 && pt.y > _rc1.top - 10 && pt.y < _rc1.bottom)// �簢���� �������� ������
			{
				_rc1.top = pt.y;
			}
			else if (pt.y < _rc1.bottom + 10 && pt.y > _rc1.bottom - 10 && pt.y > _rc1.top)// �簢���� ���ʾƷ��� ������
			{
				_rc1.bottom = pt.y;
			}
		}
		else if (pt.x < _rc1.right + 10 && pt.x > _rc1.right - 10 && mouseClick == true)// �簢���� �������� ������
		{
			_rc1.right = pt.x;
			if (pt.y < _rc1.bottom + 10 && pt.y > _rc1.bottom - 10 && pt.y > _rc1.top)// �簢���� ���������� ������
			{
				_rc1.bottom = pt.y;
			}
			else if (pt.y < _rc1.top + 10 && pt.y > _rc1.top - 10 && pt.y < _rc1.bottom)// �簢���� �����ʾƷ��� ������
			{
				_rc1.top = pt.y;
			}
		}
		else if (pt.y < _rc1.top + 10 && pt.y > _rc1.top - 10  && mouseClick == true)// �簢���� ������ ������
		{
			_rc1.top = pt.y;
		}
		else if (pt.y < _rc1.bottom + 10 && pt.y > _rc1.bottom - 10  && mouseClick == true)// �簢���� �Ʒ����� ������
		{
			_rc1.bottom = pt.y;
		}
		sizeX = _rc1.right - _rc1.left;
		sizeY = _rc1.bottom - _rc1.top;
		if (pt.x > _rc1.left && pt.x < _rc1.right && pt.y <_rc1.bottom && pt.y >_rc1.top && mouseClick == true) // �簢���� ������
		{
			_rc1.left = (_rc1.left - _rc1.right)/2 +pt.x; 
			_rc1.right = _rc1.left+ sizeX;
			_rc1.top = (_rc1.top - _rc1.bottom) / 2 + pt.y;
			_rc1.bottom = _rc1.top + sizeY;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_KEYDOWN: //Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_LEFT:	//���� ����Ű
			break;

		case VK_RIGHT:  //������ ����Ű
			break;

		case VK_UP:     //�� ����Ű
			break;

		case VK_DOWN:   //�Ʒ� ����Ű
			break;
		case VK_ESCAPE:	//esc Ű�� ������ ȭ������
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_DESTROY://�Ҹ���
		PostQuitMessage(0);
		return 0;
	}
	//������ ���ν������� ó������ ���� ������ �޼����� ó�����ش�
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//=================================================================
//	## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//=================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}