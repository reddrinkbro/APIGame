#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화
	
	IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	maptoolSetup();

	//현재타일 초기화(지형)
	_currentTile.x = 5;
	_currentTile.y = 0;

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용		
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(void)
{
	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	IMAGEMANAGER->render("tilemap", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth(), 0);

	//전체화면 왼쪽에 지형 출력
	//전체화면 왼쪽에 오브젝트 출력
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		if (_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("tilemap",
			getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}

void mainGame::maptoolSetup()
{
	//버튼 초기화
	_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "OBJ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1000, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);

	//지형 그리기 버튼으로 초기화
	_ctrSelect = CTRL_TERRAINDRAW;

	//오른쪽 샘플 맵 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//왼쪽맵 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//기본으로 깔리는 타일 셋팅
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
		//true이면 타일, false이면 오브젝트
		_tiles[i].tileState = true;
	}
}

void mainGame::setMap()
{
	//오른쪽 샘플
	//오른쪽 샘플타일 고른 이미지 인덱스 번호를 잠시 보관
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	//왼쪽 맵
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			//현재 버튼이 지형에 체크되어 있으면
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				_tiles[i].tileState = true;
			}
			//현재 버튼이 오브젝트에 체크되어 있으면
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				_tiles[i].tileState = false;
			}
			//현재 버튼이 지우개로 체크되어 있으면
			else if (_ctrSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;

				_tiles[i].obj = OBJ_NONE;
				_tiles[i].terrain = TR_END;
			}

			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}

void mainGame::save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile("save/TileMap.map",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
}

void mainGame::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("save/TileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
}

TERRAIN mainGame::terrainSelect(int frameX, int frameY)
{
	//시멘트
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}

	//흙바닥
	else if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}

	//잔디
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}

	//물
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT mainGame::objSelect(int frameX, int frameY)
{
	//탱크1
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}

	//탱크2
	else if (frameX == 19 && frameY == 7)
	{
		return OBJ_TANK2;
	}

	//1방짜리
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}

	//3방짜리 블록
	else if (frameX == 17 && frameY == 2)
	{
		return OBJ_BLOCK2;
	}

	//무적블록
	else if (frameX == 12 && frameY == 3)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCK1;
}
