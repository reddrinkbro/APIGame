#pragma once
#include "gameNode.h"
#include <math.h>

#define PI 3.141592654f

/*
- ���� -

- ���п��� �ﰢ�Լ��� �����ﰢ���� ���� �����ﰢ���� ������ ������ ��� ��Ÿ���� �Լ�

- ���ӿ���: ������ �̿��Ҷ� �ʿ��� (�߻�ü�� ������ ĳ���� �밢�� �̵� ���)

- ������ �ȴ� -> ������ �Ÿ��� �ȴ�. ��ǥ�������� �������� ����
  (End - start = �� �������� �Ÿ�)

- �� �������� ����(X,Y) ������ ���̷��� ���Ѵ�
  (deltaX,deltaY) - dalta�� ���̷��� �ǹ�

- �밢��(����)�� �Ÿ��� ���Ѵ�

- distance(����) = sqrt(deltaX * deltaX + deltaY * deltaY);

- ���� ���Ѵ� (������ ���)

- float angle = acos(deltaX / distance);
  acos(500/529)

- ������ ���� ���̷��� ���Ѵ�

- float deltaX = cos(Radians) * distance(�̵���);

- float deltaY = -sin(Radians) * distance(�̵���);

x�� ��ǥ ���ϱ�
x = cos(���� * PI / 180) * �ӵ�;

y�� ��ǥ ���ϱ�
y = -sin(���� * PI / 180) * �ӵ�;

API������ ������ ��ǥ�踦 ���µ� ������ ��ǥ��� ��ī��Ʈ ��ǥ��� �ٸ���
y���� �Ʒ��� ���������� ���� Ŀ���� ������ y�� ��ǥ�� ���Ҷ�
sin�տ� ���̳ʽ��� �ٿ��� �Ѵ�

ȣ����: �־�� ���� ���������� ��Ÿ�� ���� ���ϸ�
�������� ���̿� ���� ȣ�� ���� �߽ɰ��� 1ȣ��(����)�̴�

60�й�
PI : 3.14
���� �ѷ� : 2 * PI * ������
���� ���� : ������ * ������ * PI
PI�� ���� ���� 180��

180 degree = PI radian
1 degree = PI / 180 radian
x degree = x * PI / 180 radian
1 radian = 180 / PI degrss
x radian = x * 180 / PI degree

//��ä�� ��翡�� ������, ȣ, �߽ɰ� 3�����߿�
//2������ �˸� �ٸ� �Ѱ����� ���� �� �ִ�

����: �������� ȣ�� ���̰� ���� ���� 1�������� �����ϰ�
1���� = 57.3��

��׸�: �Ϲ������� ����ϴ� ���� ����(����)
�ѹ����� 360���� �����Ѵ�
*/

struct tagCannon
{
	POINT center;		//ĳ�� �߽���
	POINT cannonEnd;	//ĳ�� ����
	int radius;			//������
	int length;			//����
	float angle;		//���Ȱ�
};
struct bullet
{
	RECT rc;
	float bulletAngle;
	
};
class mainGame : public gameNode
{
private:
	tagCannon _cannon;
	bullet _bullet;
	vector <bullet> bulletVec;
	bool isShoot;
	float deltaX;
	float deltaY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void fire(void);
	void intersect(void);
	mainGame() {}
	~mainGame() {}
};

