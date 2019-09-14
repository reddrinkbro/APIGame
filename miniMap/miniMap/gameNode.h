#pragma once
#include "image.h"

class gameNode
{
private:
	image* _backBuffer;				//����� �̹���
	void setBackBuffer(void);		//����� �����ϱ�

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(){}
	virtual ~gameNode() {}
};

