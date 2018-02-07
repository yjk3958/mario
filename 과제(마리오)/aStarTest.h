#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStarTest : public gameNode
{
private:
	//��ü Ÿ�� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� Ÿ�� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;
	
	//���� ����� ��θ� ���� ����
	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;

	int _count;
	bool _start;

public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	//Ÿ�� ���� �Լ�
	void setTiles();
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);

	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();
};

