#pragma once
#include "gameNode.h"
#include <math.h>

#define PI 3.141592654f

/*
- 정의 -

- 수학에서 삼각함수는 직각삼각형의 각을 직각삼각형의 변들의 길이의 비로 나타내는 함수

- 게임에서: 각도를 이용할때 필요함 (발사체의 각도나 캐릭터 대각선 이동 등등)

- 두점을 안다 -> 서로의 거리를 안다. 목표지점에서 시작지점 뺀다
  (End - start = 두 점사이의 거리)

- 위 공식으로 각점(X,Y) 사이의 변이량을 구한다
  (deltaX,deltaY) - dalta는 변이량을 의미

- 대각선(빗변)의 거리를 구한다

- distance(빗변) = sqrt(deltaX * deltaX + deltaY * deltaY);

- 각을 구한다 (공식을 사용)

- float angle = acos(deltaX / distance);
  acos(500/529)

- 각도에 대한 변이량을 구한다

- float deltaX = cos(Radians) * distance(이동량);

- float deltaY = -sin(Radians) * distance(이동량);

x축 좌표 구하기
x = cos(각도 * PI / 180) * 속도;

y축 좌표 구하기
y = -sin(각도 * PI / 180) * 속도;

API에서는 윈도우 좌표계를 쓰는데 윈도우 좌표계는 데카르트 좌표계와 다르게
y축이 아래로 내려갈수록 수가 커지기 때문에 y축 좌표를 구할때
sin앞에 마이너스를 붙여야 한다

호도법: 주어는 각을 십진법으로 나타낸 것을 말하며
반지름의 길이와 같은 호에 대한 중심각을 1호도(라디안)이다

60분법
PI : 3.14
원의 둘레 : 2 * PI * 반지름
원의 넓이 : 반지름 * 반지름 * PI
PI의 라디안 값은 180도

180 degree = PI radian
1 degree = PI / 180 radian
x degree = x * PI / 180 radian
1 radian = 180 / PI degrss
x radian = x * 180 / PI degree

//부채꼴 모양에서 반지름, 호, 중심각 3가지중에
//2가지만 알면 다른 한가지를 구할 수 있다

라디안: 반지름과 호의 길이가 같은 값을 1라디안으로 정의하고
1라디안 = 57.3도

디그리: 일반적으로 사용하는 각의 단위(각도)
한바퀴를 360도로 정의한다
*/

struct tagCannon
{
	POINT center;		//캐논 중심점
	POINT cannonEnd;	//캐논 끝점
	int radius;			//반지름
	int length;			//길이
	float angle;		//라디안값
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

