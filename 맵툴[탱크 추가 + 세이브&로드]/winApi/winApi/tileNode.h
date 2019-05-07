#pragma once

//ȭ����� ����ȭ��
#define TILESIZE 32						//������ ȭ�� Ÿ�� ������
#define TILEX 20						//����ȭ�� Ÿ�� ������ X
#define TILEY 20						//����ȭ�� Ÿ�� ������ Y
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//��Ʈ������
//�����Ӽ� �����ϱ�
//������ & and | or 
//||(OR), &&(AND)
//|(OR), &(AND)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
#define ATTR_UNMOVE   0x00000001
#define ATTR_POSITION 0x00000002

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