#pragma once

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ��� �ε� (������)
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//���ҽ� ID
		HDC			hMemDC;		//�޸� DC
		HBITMAP		hBit;		//��Ʈ��
		HBITMAP		hOBit;		//�õ��Ʈ��
		int			width;		//�̹��� ����ũ��
		int			height;		//�̹��� ����ũ��
		BYTE		loadType;	//�̹��� �ε�Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸�
	BOOL			_isTrans;		//���� ���ٰ���
	COLORREF		_transColor;	//���� ���� RGB�� (����Ÿ = RGB(255, 0, 255))

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ���
	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���

public:
	image();
	~image();

	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ��� �ʱ�ȭ(������)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	//���� �÷�Ű ���� (���� ��������?, �����)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//����
	void release(void);
	
	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���ķ��� (���� ������ ��ǥ�� ���İ��� �Բ� �̹��� ����Ѵ�)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

