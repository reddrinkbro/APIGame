#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	RECT player; //�÷��̾ �����̴� �簢��
	RECT bullet; //�Ѿ�
	RECT object; //������Ʈ
	vector <RECT> bulletVec;
	vector <RECT> objectVec;
	RECT rcTemp;
	RECT playerHp;
	int time; //Ÿ�̸Ӻ���
	int count; //Ÿ�̸� ī��Ʈ ����
	int score;//����
	int objectIndex; //������Ʈ�� �ε��� ��
	bool isBulletActive; //�Ѿ��� �����̰� �Ϸ�����
	bool isBulletMove; // �Ѿ��� �����̴���
	bool isObjectMove[16];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

