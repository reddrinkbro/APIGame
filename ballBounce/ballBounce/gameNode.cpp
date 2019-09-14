#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## �ʱ�ȭ ## init(void)
//=========================
HRESULT gameNode::init(void)
{
	//Ÿ�̸� �ʱ�ȭ
	SetTimer(_hWnd, 1, 10, NULL);
	//Ű�Ŵ��� �ʱ�ȭ
	KEYMANAGER->init();
	//�����ǵ� �ʱ�ȭ
	_ballSpeed = 1;
	return S_OK;
}

//==============================
//	## ���� ## release(void)
//==============================
void gameNode::release(void)
{
	//Ÿ�̸� ����
	KillTimer(_hWnd, 1);

	//�̱��� ����
	KEYMANAGER->releaseSingleton();
}

//=============================
//	## ������Ʈ ## update(void)
//=============================
void gameNode::update(void)
{
	//���ΰ�ħ (���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´� (true => false)
	InvalidateRect(_hWnd, NULL, true);
}

//============================
//	## ���� ## render(HDC hdc)
//============================
void gameNode::render(HDC hdc)
{
}

//============================
//	## �������ν��� ## MainProc
//============================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		setBallSpeed(_ballSpeed+1);
		break;
	case WM_RBUTTONDOWN:
		setBallSpeed(_ballSpeed-1);
		if (getBallSpeed() < 1)//�� ���ǵ�� 1���� ������������
		{
			setBallSpeed(1);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}