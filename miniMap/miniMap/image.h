#pragma once

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//리소스로 로딩 (사용안함)
		LOAD_FILE,				//파일로 로딩
		LOAD_EMPTY,				//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스 ID
		HDC			hMemDC;		//메모리 DC
		HBITMAP		hBit;		//비트맵
		HBITMAP		hOBit;		//올드비트맵
		int			width;		//이미지 가로크기
		int			height;		//이미지 세로크기
		BYTE		loadType;	//이미지 로드타입

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
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨건지
	COLORREF		_transColor;	//배경색 없앨 RGB값 (마젠타 = RGB(255, 0, 255))

	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지

public:
	image();
	~image();

	//빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	//이미지 리소스로 초기화(사용안함)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화(주 사용)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//알파블렌드 초기화
	HRESULT initForAlphaBlend(void);

	//투명 컬러키 셋팅 (배경색 날릴꺼냐?, 어떤색깔)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//해제
	void release(void);
	
	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파렌더 (내가 지정한 좌표에 알파값과 함께 이미지 출력한다)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

