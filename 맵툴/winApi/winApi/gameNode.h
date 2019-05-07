#pragma once
#include "image.h"

//백버퍼 이미지를 정적변수로 만들기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

//맵툴에서 사용할 컨트롤 이넘문
enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 이미지 얻기
	image* getBackBuffer(void) { return _backBuffer; }
	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기 (화면DC)
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	int _ctrSelect;

	virtual void setMap();
	virtual void save();
	virtual void load();

	void setCtrSelect(int num) { _ctrSelect = num; }

	gameNode(){}
	virtual ~gameNode() {}
};

