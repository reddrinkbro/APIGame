#pragma once
#include "gameNode.h"

//ȭ����� ����ȭ��
#define TILESIZE 32						//������ ȭ�� Ÿ�� ������
#define TILEX 20						//����ȭ�� Ÿ�� ������ X
#define TILEY 20						//����ȭ�� Ÿ�� ������ Y
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//����
enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_NONE
};

//��ġ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	bool tileState;
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};

class mainGame : public gameNode
{
private:
	//���̺�, �ε�, ����, ������Ʈ, ���찳 ��ư
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjectDraw;
	HWND _btnEraser;

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	vector<string> _tileSaveLoad;
	int _pos[2];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���� ����
	void maptoolSetup();
	void setMap();
		
	void save();
	void load();

	//����, ������Ʈ
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	
	mainGame() {}
	~mainGame() {}
};

