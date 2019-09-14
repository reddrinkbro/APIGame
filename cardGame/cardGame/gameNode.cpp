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
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		
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