#pragma once
#include "gameNode.h"

#define CELL_WIDTH 100		//Ÿ���� ����ũ��
#define CELL_HEIGHT 50		//Ÿ���� ����ũ��

#define RADIUS_WIDTH	CELL_WIDTH / 2
#define RADIUS_HEIGHT	CELL_HEIGHT / 2
#define INIT_X 400		//�ʱ�ȭ ��ǥ
#define INIT_Y 20

#define TILE_COUNT_X 30	//Ÿ�� ����
#define TILE_COUNT_Y 30

class isoMetricScene : public gameNode
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_X];
	int _isoX, _isoY;
	int _corner;
	char str[128];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//Ÿ�ϸ� �׷��ִ� �Լ�
	void drawTileMap();
	//������ �׷��ִ� �Լ�
	void drawRhombus(int left, int top);
	//�ڳ� ����(1 ~ 4�и�)
	int getCornerIndex(int isoX, int isoY);
	//�ڳʾȿ� �Դ��� �����ϴ� �Լ�
	bool isInRhombus(int corner, int isoX, int isoY);


	isoMetricScene();
	~isoMetricScene();
};

