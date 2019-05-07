#include "stdafx.h"
#include "tankMap.h"

HRESULT tankMap::init(void)
{
	IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	this->load();

	return S_OK;
}

void tankMap::release(void)
{
}

void tankMap::update(void)
{
}

void tankMap::render(void)
{
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
}

void tankMap::save()
{
	/*
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
	*/
}

void tankMap::load()
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

	//������Ʈ ����
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_TANK1 || _tiles[i].obj == OBJ_TANK2)
		{
			_tiles[i].obj = OBJ_NONE;
		}
	}

	//�� �Ӽ� ����
	//������ �� �� ������Ʈ���� ��ũ�� �����ٴ� �� ����
	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TR_WATER) _attribute[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK1) _attribute[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK2) _attribute[i] = ATTR_UNMOVE;
	}
}
