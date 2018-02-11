#pragma once
#include "gameNode.h"
#include <vector>

#define TILESIZE 16

//================== 나중에 수정할부분
#define TILEX 20
#define TILEY 20
//===================
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY
//===================여기도
#define SAMPLETILEX 20
#define SAMPLETILEY 9


enum TERRAIN
{
	TR_INAIR,TR_ONLAND
};
enum OBJECT
{
	OBJ_PIPE,
	OBJ_HILL,
	OBJ_BLOCK,
	OBJ_ITEMBOX,
	OBJ_NONE
};
enum ITEM
{
	ITEM_COIN,
	ITEM_ITEM,
	ITEM_NONE
};
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	ITEM item;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};
struct  tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
struct  tagCurrentTile
{
	int x;
	int y;
};


class mapTool : public gameNode
{
private : 
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjectDraw;
	HWND _btnItemDraw;
	HWND _btnEraser;
	HWND _btnDrag;


	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile			_tiles[TILEX * TILEY];


	image* _image;
	int _pos[2];
public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

									//맵 셋팅 관련 함수
	virtual void setup();
	virtual void setMap();

	//저장, 불러오기
	virtual void save();
	virtual void load();

	//TERRAIN terrainSelect(int frameX, int frameY);
	//OBJECT objSelect(int frameX, int frameY);
	//ITEM itemSelect(int frameX, int frameY);
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	mapTool();
	~mapTool();
};

