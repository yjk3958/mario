#pragma once
#include "gameNode.h"

class modeSelect : public gameNode
{
public:
	modeSelect();
	~modeSelect();

	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�
};

