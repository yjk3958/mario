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

	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

