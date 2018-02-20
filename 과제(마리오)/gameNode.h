#pragma once
#include "image.h"


enum CTRL
{
	CTRL_SAVE,			//세이브		버튼 메시지
	CTRL_LOAD,			//로드		버튼 메시지
	CTRL_TERRAINDRAW,	//지형		버튼 메시지 terrain == 지형
	CTRL_OBJDRAW,		//오브젝트	버튼 메시지
	CTRL_ERASER,		//지우개		버튼 메시지
	CTRL_BOXMAKE,		//드래그박스
	CTRL_TILEMAKE,
	CTRL_END
};


//백버퍼라는 빈 비트맵 이미지를 하나 설정해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//매니저등을 초기화 할 것이냐

public:
	virtual HRESULT init(void);		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수
	int _ctrSelect;


	//맵 셋팅 함수
	virtual void setMap(void);

	//저장, 로드
	virtual void save(void);
	virtual void load(void);

	void setCtrlSelect(int num) { _ctrSelect = num; }

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }


	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

