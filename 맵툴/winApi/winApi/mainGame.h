#pragma once
#include "gameNode.h"

//화면왼쪽 게임화면
#define TILESIZE 32						//오른쪽 화면 타일 사이즈
#define TILEX 20						//왼쪽화면 타일 사이즈 X
#define TILEY 20						//왼쪽화면 타일 사이즈 Y
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//지형
enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

//오브젝트
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

//위치좌표
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//타일구조체
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

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

class mainGame : public gameNode
{
private:
	//세이브, 로드, 지형, 오브젝트, 지우개 버튼
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

	//맵툴 셋팅
	void maptoolSetup();
	void setMap();
		
	void save();
	void load();

	//지형, 오브젝트
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	
	mainGame() {}
	~mainGame() {}
};

