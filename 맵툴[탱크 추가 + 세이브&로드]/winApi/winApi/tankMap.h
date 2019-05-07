#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tankMap : public gameNode
{
private:

	tagTile _tiles[TILEX * TILEY];		  //Ÿ��
	DWORD _attribute[TILEX * TILEY];	  //�Ӽ�

	int _pos[2];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void save();
	void load();

	tagTile* getTiles() { return _tiles; }
	int getPosFirst() { return 0; }
	
	DWORD* getAttribute() { return _attribute; }
	tankMap() {}
	~tankMap() {}
};

