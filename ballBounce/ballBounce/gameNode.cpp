#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## 초기화 ## init(void)
//=========================
HRESULT gameNode::init(void)
{
	//타이머 초기화
	SetTimer(_hWnd, 1, 10, NULL);
	//키매니져 초기화
	KEYMANAGER->init();
	//공스피드 초기화
	_ballSpeed = 1;
	return S_OK;
}

//==============================
//	## 해제 ## release(void)
//==============================
void gameNode::release(void)
{
	//타이머 해제
	KillTimer(_hWnd, 1);

	//싱글톤 해제
	KEYMANAGER->releaseSingleton();
}

//=============================
//	## 업데이트 ## update(void)
//=============================
void gameNode::update(void)
{
	//새로고침 (고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	InvalidateRect(_hWnd, NULL, true);
}

//============================
//	## 렌더 ## render(HDC hdc)
//============================
void gameNode::render(HDC hdc)
{
}

//============================
//	## 메인프로시져 ## MainProc
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
		if (getBallSpeed() < 1)//공 스피드는 1보다 느려질수없다
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