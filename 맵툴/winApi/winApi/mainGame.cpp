#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	
	IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	maptoolSetup();

	//����Ÿ�� �ʱ�ȭ(����)
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
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���		
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	IMAGEMANAGER->render("tilemap", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth(), 0);

	//��üȭ�� ���ʿ� ���� ���
	//��üȭ�� ���ʿ� ������Ʈ ���
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
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}

void mainGame::maptoolSetup()
{
	//��ư �ʱ�ȭ
	_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "OBJ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 900, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1000, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);

	//���� �׸��� ��ư���� �ʱ�ȭ
	_ctrSelect = CTRL_TERRAINDRAW;

	//������ ���� �� ����
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

	//���ʸ� ����
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

	//�⺻���� �򸮴� Ÿ�� ����
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
		//true�̸� Ÿ��, false�̸� ������Ʈ
		_tiles[i].tileState = true;
	}
}

void mainGame::setMap()
{
	//������ ����
	//������ ����Ÿ�� �� �̹��� �ε��� ��ȣ�� ��� ����
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	//���� ��
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			//���� ��ư�� ������ üũ�Ǿ� ������
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				_tiles[i].tileState = true;
			}
			//���� ��ư�� ������Ʈ�� üũ�Ǿ� ������
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				_tiles[i].tileState = false;
			}
			//���� ��ư�� ���찳�� üũ�Ǿ� ������
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
	//�ø�Ʈ
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}

	//��ٴ�
	else if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}

	//�ܵ�
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}

	//��
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT mainGame::objSelect(int frameX, int frameY)
{
	//��ũ1
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}

	//��ũ2
	else if (frameX == 19 && frameY == 7)
	{
		return OBJ_TANK2;
	}

	//1��¥��
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}

	//3��¥�� ���
	else if (frameX == 17 && frameY == 2)
	{
		return OBJ_BLOCK2;
	}

	//�������
	else if (frameX == 12 && frameY == 3)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCK1;
}
