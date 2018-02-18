#pragma once
#include "gameNode.h"

class modeSelect : public gameNode
{
private : 
	HWND _btnMapTool;
	HWND _btnPlay;

public:
	modeSelect();
	~modeSelect();

	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

