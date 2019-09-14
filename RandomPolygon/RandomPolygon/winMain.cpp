#include "stdafx.h"

//=====================
//	## �������� ##
//=====================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

//======================
//	## �Լ� ���漱�� ##
//======================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
bool mouseClick = false;
int centerX;
int centerY;
int randX;
int randY;
POINT polygonPoint[3];
double PI = 3.14;
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
	switch (iMessage)
	{
	case WM_CREATE: //������ == �ʱ�ȭ

		centerX = WINSIZEX / 2;
		centerY = WINSIZEY / 2;
		break;
	case WM_PAINT:	//��¿� ���� ������ ����Ѵ�(����, �׸�, ������� ȭ�鿡 ���̴� ����)
		hdc = BeginPaint(hWnd, &ps);		
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN: //���콺 ���� ��ư�� �������� �޼��� �߻�
		hdc = GetDC(hWnd);
		mouseClick = true;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		centerX = RND->getInt(pt.x);
		centerY = RND->getInt(pt.y);
		randX = RND->getInt(WINSIZEX); // �ﰢ�� ���鶧 ����ϱ� ���� ��������
		randY = RND->getInt(WINSIZEY);
		polygonPoint[0] = { centerX, centerY };//�ﰢ�� ���� �������ش�
		polygonPoint[1] = { pt.x, pt.y };
		polygonPoint[2] = { randX, randY };
		if (RND->getInt(GetTickCount()) % 3 == 0) //�������� 0�̸� �簢��
		{
			Rectangle(hdc, centerX, centerY, pt.x+100, pt.y+100);
		}
		else if (RND->getInt(GetTickCount()) % 3 == 1)//�������� 1�̸� ��
		{
			EllipseMakeCenter(hdc, pt.x, pt.y, centerX, centerY);
		}
		else//�������� 2�̸� �ﰢ��
		{
			Polygon(hdc, polygonPoint, 3);
		}
		break;
	case WM_RBUTTONDOWN: //���콺 ������ ��ư�� �������� �޼��� �߻�
		break;

	case WM_KEYDOWN:	//Ű���� Ű�� �������� �޼��� �߻�
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