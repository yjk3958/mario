#pragma once
#include "image.h"


enum CTRL
{
	CTRL_SAVE,			//���̺�		��ư �޽���
	CTRL_LOAD,			//�ε�		��ư �޽���
	CTRL_TERRAINDRAW,	//����		��ư �޽��� terrain == ����
	CTRL_OBJDRAW,		//������Ʈ	��ư �޽���
	CTRL_ERASER,		//���찳		��ư �޽���
	CTRL_END
};


//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//�Ŵ������� �ʱ�ȭ �� ���̳�

public:
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�
	int _ctrSelect;


	//�� ���� �Լ�
	virtual void setMap(void);

	//����, �ε�
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

