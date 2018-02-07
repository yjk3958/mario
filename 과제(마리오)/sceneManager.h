#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

//��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>			 mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;	//���� ��
	static gameNode* _loadingScene;	//�ε� ��(�Ⱦ��ϵ�)
	static gameNode* _readyScene;	//��� ��

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;			//Ȥ�� ���� �־���� ������� ID

public:
	sceneManager();
	~sceneManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//friend�� �����ϸ� Ŭ������ private���� �׳� ���� ������ �Ѵ�
	//�����ϸ� �ȵǴµ�, ������ ���� 1~2�������� �صθ� ���� �� ������ �ص���
	friend DWORD CALLBACK loadingThread(LPVOID prc);

};

