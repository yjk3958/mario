#pragma once
#include "gameNode.h"
#include <vector>

#define TILESIZE 16

//================== 나중에 수정할부분
#define TILEBASEX 20
#define TILEBASEY 20


enum TERRAIN
{
	TR_INAIR,
	TR_ONLAND,
	TR_NONE
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

enum CTRLDIRECTION
{
	CTRL_UP,
	CTRL_DOWN,
	CTRL_LEFT,
	CTRL_RIGHT,
	CTRL_NONE
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
	vector<tagTile> _vTile;
	vector<tagTile>::iterator _viTile;

	vector<tagSampleTile> _vSampleTile;
	vector<tagSampleTile>::iterator _viSampleTile;

private : 
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjectDraw;
	HWND _btnItemDraw;
	HWND _btnEraser;
	HWND _btnDrag;

	tagCurrentTile	_currentTile;

	image* _image;
	int _pos[2];
	int _page;

	int _currentFrameX;
	int _currentFrameY;
	bool _checkBox;
	CTRL _currentCtrl;

	RECT _ctrlCameraRect[4];
	RECT _ctrlPage[2];
	RECT _cameraBox;
	RECT _sampleBox;
	POINT _basePoint;
	POINT _endPoint;


public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

									//맵 셋팅 관련 함수
	virtual void setup();
	virtual void setMap();
	virtual void setSampleTile();


	//저장, 불러오기
	virtual void save();
	virtual void load();


	//TERRAIN terrainSelect(int frameX, int frameY);
	//OBJECT objSelect(int frameX, int frameY);
	//ITEM itemSelect(int frameX, int frameY);
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	vector<tagTile> getVTile() { return _vTile; }
	void setVTileObj(int i, OBJECT obj) { _vTile[i].obj = obj; }
	void setVTileItem(int i, ITEM item) { _vTile[i].item = item; }
};

