#pragma once

class gameNode
{
private :
	int _ballSpeed;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	int getBallSpeed() { return _ballSpeed; }
	void setBallSpeed(int ballSpeed) { _ballSpeed = ballSpeed; }
	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(){}
	virtual ~gameNode() {}
};

